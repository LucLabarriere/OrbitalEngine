#pragma once

#include "OrbitalEngine/Utils/Logger.h"
#include "OrbitalEngine/Logic/Entity.h"
#include "OrbitalEngine/Components.h"

using namespace OrbitalEngine;

class TreeNode
{
public:
	TreeNode(const Entity& entity)
		: m_entity(entity)
	{
		auto& hierarchy = m_entity.get<Components::Hierarchy>();
		const auto& children = hierarchy.getChildren();
		for (auto& child : children)
		{
			m_children.push_back(child);
		}

		m_title = m_entity.get<Components::Tag>();
	}

	void render()
	{
		bool nodeOpen = false;
		if (m_children.size() == 0)
		{
			ImGui::TreeNodeEx(m_title.c_str(), ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen);
		}
		else
		{
			nodeOpen = ImGui::TreeNode(m_title.c_str());
		}

		// Source
		if (ImGui::BeginDragDropSource())
		{
			ImGui::SetDragDropPayload("TreeNode", (const void*)&m_entity, sizeof(m_entity));
			ImGui::EndDragDropSource();
		}

		// Target
		if (ImGui::BeginDragDropTarget())
		{
			const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("TreeNode");
			if (payload)
			{
				Entity e = *static_cast<Entity*>(payload->Data);
				e.get<Components::Hierarchy>().setParent(m_entity);
			}
			ImGui::EndDragDropTarget();
		}

		if (nodeOpen)
		{
			for (auto& node : m_children)
				node.render();

			ImGui::TreePop();
		}
	}

private:
	Entity m_entity;
	std::vector<TreeNode> m_children;
	std::string m_title;
};
