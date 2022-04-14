#include "TreeNode.h"
#include "HierarchyPanel.h"
#include "Inspector.h"

TreeNode::TreeNode(const Entity& entity, Ref<HierarchyPanel> panel)
	: m_entity(entity), m_panel(panel)
{
	auto& hierarchy = m_entity.get<Components::Hierarchy>();
	const auto& children = hierarchy.getChildren();
	for (auto& child : children)
	{
		m_children.push_back(TreeNode(child, m_panel));
	}

	m_title = m_entity.get<Components::Tag>();
}

void TreeNode::render()
{
	bool nodeOpen = false;
	ImGuiTreeNodeFlags nodeFlags = 
		ImGuiTreeNodeFlags_OpenOnArrow |
		ImGuiTreeNodeFlags_OpenOnDoubleClick |
		ImGuiTreeNodeFlags_SpanAvailWidth;

	if (m_panel->getSelectedEntityHandle() == m_entity.getHandle())
	{
		nodeFlags |= ImGuiTreeNodeFlags_Selected;
	}

	if (m_children.size() == 0)
	{
		nodeFlags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
		ImGui::TreeNodeEx(m_title.c_str(), nodeFlags);
	}
	else
	{
		nodeOpen = ImGui::TreeNodeEx(m_title.c_str(), nodeFlags);
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

	if (ImGui::IsItemClicked())
	{
		m_panel->setSelectedEntity(m_entity);
		Inspector::SetEntity(m_entity);
	}

	if (nodeOpen)
	{
		for (auto& node : m_children)
			node.render();

		ImGui::TreePop();
	}
}
