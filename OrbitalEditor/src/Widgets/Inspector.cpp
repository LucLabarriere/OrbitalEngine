#include "Inspector.h"

Inspector::Inspector(Ref<Scene>& scene)
	: m_scene(scene), m_entity()
{

}

void Inspector::render()
{
	ImGui::Begin("Inspector");
	if (m_entity.isValid())
	{
		auto& tag = m_entity.get<Components::Tag>();
		auto& layerId= m_entity.get<LayerID>();
		auto* transform = m_entity.tryGet<Components::Transform>();
		auto* meshRenderer = m_entity.tryGet<Components::MeshRenderer>();

		if (ImGui::CollapsingHeader("General"))
		{
			// Tag
			char buffer[64];
			strcpy(buffer, tag.c_str());
			ImGui::InputText("Tag", buffer, 64);
			Components::Tag tag(buffer);

			if (buffer[0] != 0)
				m_scene->renameEntity(m_entity, tag);
			
			//LayerID
			int bufferLayerId = (int)layerId;
			ImGui::Combo("LayerID", &bufferLayerId, m_layerRange, OE_LAST_LAYER + 1);

			if ((LayerID)bufferLayerId != layerId)
			{
				m_entity.changeLayer(bufferLayerId);
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
					m_entity.add<Components::MeshRenderer>(MeshManager::Get("Cube"), false, true);
					if (!transform)
						m_entity.add<Components::Transform>();
				}
			}
			if (!transform)
			{
				if (ImGui::Selectable("Transform"))
				{
					m_entity.add<Components::Transform>();
				}
			}
			ImGui::EndPopup();
		}
	}
	ImGui::End();
}
