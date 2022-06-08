#include "Inspector.h"
#include "OrbitalEngine/Utils.h"
#include "OrbitalEngine/Components.h"


Inspector::Inspector()
	: mObject()
{

}

void Inspector::RenderImpl()
{
	ImGui::Begin("Inspector");
	switch (mObject.Tag)
	{
		case InspectedObjectTag::Entity:
		{
			RenderEntity();
			break;
		}
		case InspectedObjectTag::Texture:
		{
			RenderTexture();
			break;
		}
		case InspectedObjectTag::Text:
		{
			RenderText();
			break;
		}
		case InspectedObjectTag::Material:
		{
			RenderMaterial();
			break;
		}
	}
	ImGui::End();
}

void Inspector::RenderEntity()
{
	auto& entity = std::get<Entity>(mObject.Value);

	if (entity.IsValid())
	{
		auto& tag = entity.GetComponent<Tag>();
		auto& layerId = entity.GetComponent<LayerID>();
		auto& hiearchy = entity.GetComponent<Hierarchy>();
		auto* transform = entity.TryGetComponent<Transform>();
		auto* meshRenderer = entity.TryGetComponent<MeshRenderer>();
		auto* directionalLight = entity.TryGetComponent<DirectionalLight>();
		auto* pointLight = entity.TryGetComponent<PointLight>();
		auto* spotLight = entity.TryGetComponent<SpotLight>();

		if (ImGui::CollapsingHeader("General"))
		{
			// Tag
			char buffer[64];
			strcpy(buffer, tag.c_str());
			ImGui::InputText("Tag", buffer, 64);
			Tag tag(buffer);

			if (buffer[0] != 0)
				OE::ActiveScene->RenameEntity(entity, tag);

			//LayerID
			int bufferLayerId = (int)layerId;
			ImGui::Combo("LayerID", &bufferLayerId, mLayerRange, OE_LAST_LAYER + 1);

			if ((LayerID)bufferLayerId != layerId)
			{
				entity.ChangeLayer(bufferLayerId);
			}
		}

		if (transform)
		{
			if (ImGui::CollapsingHeader("Transform"))
			{
				ImGui::DragFloat3("Position", &transform->GetPosition()[0], 0.001f);
				ImGui::DragFloat3("Rotation", &transform->GetRotation()[0], 1.0f);
				ImGui::DragFloat3("Scale", &transform->GetScale()[0], 0.01f);

				if (ImGui::Button("X"))
				{
					entity.RemoveComponent<Transform>();
				}
			}
		}

		if (meshRenderer)
		{
			if (ImGui::CollapsingHeader("MeshRenderer"))
			{
				MeshRenderer::DrawData drawData = meshRenderer->GetDrawData();

				ImGui::Checkbox("Static", &drawData.staticDraw);
				ImGui::Checkbox("Batched", &drawData.batchDraw);
				ImGui::Checkbox("Hidden", &drawData.hidden);

				if (drawData != meshRenderer->GetDrawData())
				{
					meshRenderer->SetDrawData(drawData);

					// TODO correct here, set hidden should be done for the children of the children
					for (auto child : hiearchy)
					{
						child.GetComponent<MeshRenderer>().SetHidden(drawData.hidden);
					}
				}

				// Mesh
				int currentItem = 0;
				auto meshTags = MeshManager::GetAvailable();

				for (size_t i = 0; i < meshTags.size(); i++)
				{
					if (meshTags[i] == meshRenderer->GetMesh().lock()->GetTag().c_str())
						currentItem = i;
				}

				ImGui::Combo("Mesh", &currentItem, meshTags.data(), meshTags.size());

				if (meshTags[currentItem] != meshRenderer->GetMesh().lock()->GetTag())
				{
					meshRenderer->SetMesh(meshTags[currentItem]);
				}

				// Material
				currentItem = 0;
				auto materialTags = MaterialManager::GetAvailable();

				for (size_t i = 0; i < materialTags.size(); i++)
				{
					if (materialTags[i] == meshRenderer->GetMaterial().lock()->GetTag().c_str())
						currentItem = i;
				}

				ImGui::Combo("Material", &currentItem, materialTags.data(), materialTags.size());

				if (materialTags[currentItem] != meshRenderer->GetMaterial().lock()->GetTag())
				{
					meshRenderer->SetMaterial(materialTags[currentItem]);
				}

				ImGui::DragFloat2("TexCoords multiplicator", &meshRenderer->GetTexCoordsMultiplicator()[0], 0.1f, 0.0f, 10.0f);

				// Delete
				if (ImGui::Button("X"))
				{
					entity.RemoveComponent<MeshRenderer>();
					meshRenderer->Destroy();
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
					entity.RemoveComponent<DirectionalLight>();
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
					entity.RemoveComponent<PointLight>();
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
					entity.RemoveComponent<SpotLight>();
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
					{
						transform = &entity.AddComponent<Transform>();
					}
					entity.AddComponent<MeshRenderer>("Cube", transform);
				}
			}
			if (!transform)
			{
				if (ImGui::Selectable("Transform"))
				{
					entity.AddComponent<Transform>();
				}
			}
			if (!directionalLight)
			{
				if (ImGui::Selectable("DirectionalLight"))
				{
					entity.AddComponent<DirectionalLight>();
				}
			}
			if (!pointLight)
			{
				if (ImGui::Selectable("PointLight"))
				{
					if (!transform)
					{
						entity.AddComponent<Transform>();
						transform = entity.TryGetComponent<Transform>();
					}
					entity.AddComponent<PointLight>(&transform->GetPosition());
				}
			}
			if (!spotLight)
			{
				if (ImGui::Selectable("SpotLight"))
				{
					if (!transform)
					{
						entity.AddComponent<Transform>();
						transform = entity.TryGetComponent<Transform>();
					}
					entity.AddComponent<SpotLight>(&transform->GetPosition());
				}
			}
			ImGui::EndPopup();
		}

		ImGui::PushStyleColor(ImGuiCol_Button, { 1.0f, 0.1f, 0.1f, 1.0f });
		if (ImGui::Button("Delete entity"))
		{
			OE::ActiveScene->RequireDelete(entity);
		}
		ImGui::PopStyleColor();
	}
}

void Inspector::RenderTexture()
{
	auto texture = std::get<WeakRef<Texture>>(mObject.Value).lock();

	float maxSize = 256.0f;
	float width = (float)texture->GetWidth();
	float height = (float)texture->GetHeight();


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
	ImGui::Text("Name: %s", texture->GetTag().c_str());
	ImGui::Text("Width: %u", texture->GetWidth());
	ImGui::Text("Height: %u", texture->GetHeight());
	ImGui::Image(
		(void*)(intptr_t)texture->GetRendererId(),
		ImVec2(width, height),
		ImVec2(0, 0),
		ImVec2(1, 1)
	);

	// WrapS
	int currentItem = 0;
	std::vector<const char*> wrapNames = {
		"Repeat", "Mirrored repeat", "Clamp to edge", "Clamp to border"
	};

	std::vector<unsigned int> wrapValues = {
		OE_REPEAT, OE_MIRRORED_REPEAT, OE_CLAMP_TO_EDGE, OE_CLAMP_TO_BORDER
	};

	for (size_t i = 0; i < wrapValues.size(); i++)
	{
		if (wrapValues[i] == texture->GetWrapS())
			currentItem = i;
	}

	ImGui::Combo("Wrap S", &currentItem, wrapNames.data(), wrapNames.size());

	if (wrapValues[currentItem] != texture->GetWrapS())
	{
		texture->SetWrapS(wrapValues[currentItem]);
	}

	// WrapT
	currentItem = 0;

	for (size_t i = 0; i < wrapValues.size(); i++)
	{
		if (wrapValues[i] == texture->GetWrapT())
			currentItem = i;
	}

	ImGui::Combo("Wrap T", &currentItem, wrapNames.data(), wrapNames.size());

	if (wrapValues[currentItem] != texture->GetWrapT())
	{
		texture->SetWrapT(wrapValues[currentItem]);
	}

	// MinFilter
	currentItem = 0;
	std::vector<const char*> filterNames = { "Nearest", "Linear" };

	std::vector<unsigned int> filterValues = { OE_NEAREST, OE_LINEAR };

	for (size_t i = 0; i < filterValues.size(); i++)
	{
		if (filterValues[i] == texture->GetMinFilter())
			currentItem = i;
	}

	ImGui::Combo("Minify filter", &currentItem, filterNames.data(), filterNames.size());

	if (filterValues[currentItem] != texture->GetMinFilter())
	{
		texture->SetMinFilter(filterValues[currentItem]);
	}

	// MagFilter
	currentItem = 0;

	for (size_t i = 0; i < filterValues.size(); i++)
	{
		if (filterValues[i] == texture->GetMagFilter())
			currentItem = i;
	}

	ImGui::Combo("Magnify filter", &currentItem, filterNames.data(), filterNames.size());

	if (filterValues[currentItem] != texture->GetMagFilter())
	{
		texture->SetMagFilter(filterValues[currentItem]);
	}
}

void Inspector::RenderText()
{
	auto& text = std::get<std::string>(mObject.Value);
	ImGui::Text(text.c_str());
}

void Inspector::RenderMaterial()
{
	auto material = std::get<WeakRef<Material>>(mObject.Value).lock();
	ImGui::Text("Material");
	ImGui::Text("Name: %s", material->GetTag().c_str());
	ImGui::DragFloat("Ambient", &material->GetAmbient(), 0.02f, 0.0, 1.0f);
	ImGui::ColorEdit3("Diffuse", &material->GetDiffuseTint()[0]);
	ImGui::ColorEdit3("Specular", &material->GetSpecularTint()[0]);
	ImGui::DragFloat("shininess", &material->GetShininess());
}
