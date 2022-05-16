#include "Inspector.h"

Inspector::Inspector(Ref<Scene>& scene)
	: m_scene(scene), m_object()
{

}

void Inspector::render()
{
	ImGui::Begin("Inspector");
	switch (m_object.Tag)
	{
		case InspectedObjectTag::Entity:
		{
			renderEntity();
			break;
		}
		case InspectedObjectTag::Texture:
		{
			renderTexture();
			break;
		}
		case InspectedObjectTag::Text:
		{
			renderText();
			break;
		}
	}
	ImGui::End();
}

void Inspector::renderEntity()
{
	auto& entity = std::get<Entity>(m_object.Value);

	if (entity.isValid())
	{
		auto& tag = entity.get<Components::Tag>();
		auto& layerId = entity.get<LayerID>();
		auto& hiearchy = entity.get<Components::Hierarchy>();
		auto* transform = entity.tryGet<Components::Transform>();
		auto* meshRenderer = entity.tryGet<Components::MeshRenderer>();
		auto* directionalLight = entity.tryGet<Components::DirectionalLight>();
		auto* pointLight = entity.tryGet<Components::PointLight>();
		auto* spotLight = entity.tryGet<Components::SpotLight>();

		if (ImGui::CollapsingHeader("General"))
		{
			// Tag
			char buffer[64];
			strcpy(buffer, tag.c_str());
			ImGui::InputText("Tag", buffer, 64);
			Components::Tag tag(buffer);

			if (buffer[0] != 0)
				m_scene->renameEntity(entity, tag);

			//LayerID
			int bufferLayerId = (int)layerId;
			ImGui::Combo("LayerID", &bufferLayerId, m_layerRange, OE_LAST_LAYER + 1);

			if ((LayerID)bufferLayerId != layerId)
			{
				entity.changeLayer(bufferLayerId);
			}
		}

		if (transform)
		{
			if (ImGui::CollapsingHeader("Transform"))
			{
				ImGui::DragFloat3("Position", &transform->Position()[0], 0.001f);
				ImGui::DragFloat3("Rotation", &transform->Rotation()[0], 1.0f);
				ImGui::DragFloat3("Scale", &transform->Scale()[0], 0.01f);

				if (ImGui::Button("X"))
				{
					entity.remove<Components::Transform>();
				}
			}
		}

		if (meshRenderer)
		{
			if (ImGui::CollapsingHeader("MeshRenderer"))
			{

				ImGui::Checkbox("Static", &meshRenderer->StaticDraw);
				ImGui::Checkbox("Batched", &meshRenderer->BatchedDraw);
				ImGui::Checkbox("Hidden", &meshRenderer->Hidden);

				for (auto child : hiearchy)
				{
					child.get<Components::MeshRenderer>().Hidden = meshRenderer->Hidden;
				}

				int currentItem = 0;
				auto meshTags = MeshManager::GetAvailableMeshes();

				for (size_t i = 0; i < meshTags.size(); i++)
				{
					if (meshTags[i] == meshRenderer->Mesh.lock()->getTag().c_str())
						currentItem = i;
				}

				ImGui::Combo("Mesh", &currentItem, meshTags.data(), meshTags.size());

				if (meshTags[currentItem] != meshRenderer->Mesh.lock()->getTag())
				{
					meshRenderer->setMesh(meshTags[currentItem]);
				}
				if (ImGui::Button("X"))
				{
					entity.remove<Components::MeshRenderer>();
					meshRenderer->destroy();
				}
			}
		}

		if (directionalLight)
		{
			if (ImGui::CollapsingHeader("DirectionalLight"))
			{
				ImGui::DragFloat3("Direction", &directionalLight->Direction[0], 0.05f, -1.0f, 1.0f);
				ImGui::ColorEdit3("Ambient", &directionalLight->Ambient[0]);
				ImGui::ColorEdit3("Diffuse", &directionalLight->Diffuse[0]);
				ImGui::ColorEdit3("Specular", &directionalLight->Specular[0]);
				if (ImGui::Button("X"))
				{
					entity.remove<Components::DirectionalLight>();
				}
			}
		}

		if (pointLight)
		{
			if (ImGui::CollapsingHeader("PointLight"))
			{
				ImGui::DragFloat3("Position", &(*pointLight->Position)[0], 0.05f);
				ImGui::ColorEdit3("Ambient", &pointLight->Ambient[0]);
				ImGui::ColorEdit3("Diffuse", &pointLight->Diffuse[0]);
				ImGui::ColorEdit3("Specular", &pointLight->Specular[0]);
				ImGui::Text("Attenuation");
				ImGui::DragFloat("Constant", &pointLight->ConstantAttenuation, 0.01f);
				ImGui::DragFloat("Linear", &pointLight->LinearAttenuation, 0.01f);
				ImGui::DragFloat("Quadratic", &pointLight->QuadraticAttenuation, 0.001f);
				if (ImGui::Button("X"))
				{
					entity.remove<Components::PointLight>();
				}
			}
		}

		if (spotLight)
		{
			if (ImGui::CollapsingHeader("SpotLight"))
			{
				ImGui::DragFloat3("Position", &(*spotLight->Position)[0], 0.05f);
				ImGui::DragFloat3("Direction", &spotLight->Direction[0], 0.05f, -1.0f, 1.0f);
				ImGui::ColorEdit3("Ambient", &spotLight->Ambient[0]);
				ImGui::ColorEdit3("Diffuse", &spotLight->Diffuse[0]);
				ImGui::ColorEdit3("Specular", &spotLight->Specular[0]);
				ImGui::Text("Attenuation");
				ImGui::DragFloat("Constant", &spotLight->ConstantAttenuation, 0.01f);
				ImGui::DragFloat("Linear", &spotLight->LinearAttenuation, 0.01f);
				ImGui::DragFloat("Quadratic", &spotLight->QuadraticAttenuation, 0.001f);
				ImGui::Text("Size");
				ImGui::DragFloat("Cutoff", &spotLight->Cutoff, 0.01f);
				ImGui::DragFloat("Edge %", &spotLight->Edge, 0.01f);
				if (ImGui::Button("X"))
				{
					entity.remove<Components::SpotLight>();
				}
			}
		}

		if (ImGui::Button("Add component"))
		{
			ImGui::OpenPopup("add_component_popup");
		}

		ImGui::SameLine();
		if (ImGui::BeginPopup("add_component_popup"))
		{
			if (!meshRenderer)
			{
				if (ImGui::Selectable("MeshRenderer"))
				{
					if (!transform)
						entity.add<Components::Transform>();
					entity.add<Components::MeshRenderer>("Cube", transform);
				}
			}
			if (!transform)
			{
				if (ImGui::Selectable("Transform"))
				{
					entity.add<Components::Transform>();
				}
			}
			if (!directionalLight)
			{
				if (ImGui::Selectable("DirectionalLight"))
				{
					entity.add<Components::DirectionalLight>();
				}
			}
			if (!pointLight)
			{
				if (ImGui::Selectable("PointLight"))
				{
					if (!transform)
					{
						entity.add<Components::Transform>();
						transform = entity.tryGet<Components::Transform>();
					}
					entity.add<Components::PointLight>(&transform->Position());
				}
			}
			if (!spotLight)
			{
				if (ImGui::Selectable("SpotLight"))
				{
					if (!transform)
					{
						entity.add<Components::Transform>();
						transform = entity.tryGet<Components::Transform>();
					}
					entity.add<Components::SpotLight>(&transform->Position());
				}
			}
			ImGui::EndPopup();
		}

		ImGui::PushStyleColor(ImGuiCol_Button, { 1.0f, 0.1f, 0.1f, 1.0f });
		if (ImGui::Button("Delete entity"))
		{
			m_scene->requireDelete(entity);
		}
		ImGui::PopStyleColor();
	}
}

void Inspector::renderTexture()
{
	auto& texture = std::get<Ref<Texture>>(m_object.Value);

	float maxSize = 256.0f;
	float width = (float)texture->getWidth();
	float height = (float)texture->getHeight();


	if (width > height)
	{
		float scaling = width / maxSize;
		width = maxSize;
		height /= scaling;
	}
	else
	{
		float scaling = height / maxSize;
		height = maxSize;
		width /= scaling;
	}

	ImGui::Text("Texture");
	ImGui::Text("name: %s", texture->getTag().c_str());
	ImGui::Text("width: %u", texture->getWidth());
	ImGui::Text("height: %u", texture->getHeight());
	ImGui::Image(
		(void*)(intptr_t)texture->getRendererId(),
		ImVec2(width, height),
		ImVec2(0, 0),
		ImVec2(1, 1)
	);
}

void Inspector::renderText()
{
	auto& text = std::get<std::string>(m_object.Value);
	ImGui::Text(text.c_str());
}
