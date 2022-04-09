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
		auto* transform = entity.tryGet<Components::Transform>();
		auto* meshRenderer = entity.tryGet<Components::MeshRenderer>();

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
				ImGui::DragFloat3("Position", &transform->Position[0], 0.001f);
				ImGui::DragFloat3("Rotation", &transform->Rotation[0], 1.0f);
				ImGui::DragFloat3("Scale", &transform->Scale[0], 0.01f);
			}
		}

		if (meshRenderer)
		{
			if (ImGui::CollapsingHeader("MeshRenderer"))
			{

				ImGui::Checkbox("Static", &meshRenderer->StaticDraw);
				ImGui::Checkbox("Batched", &meshRenderer->BatchedDraw);
				ImGui::Checkbox("Hidden", &meshRenderer->Hidden);

				int currentItem = 0;
				auto meshTags = MeshManager::GetAvailableMeshes();

				for (size_t i = 0; i < meshTags.size(); i++)
				{
					if (meshTags[i] == meshRenderer->Mesh->getTag().c_str())
						currentItem = i;
				}


				ImGui::Combo("Mesh", &currentItem, meshTags.data(), meshTags.size());
				meshRenderer->Mesh = MeshManager::Get(meshTags[currentItem]);
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
					entity.add<Components::MeshRenderer>(MeshManager::Get("Cube"), false, true);
					if (!transform)
						entity.add<Components::Transform>();
				}
			}
			if (!transform)
			{
				if (ImGui::Selectable("Transform"))
				{
					entity.add<Components::Transform>();
				}
			}
			ImGui::EndPopup();
		}
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
	ImGui::Text("name: %s", texture->getName().c_str());
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
