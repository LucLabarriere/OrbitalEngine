#include "TreeNode.h"
#include "HierarchyPanel.h"
#include "Inspector.h"

TreeNode::TreeNode()
	: m_entity(), m_panel(nullptr)
{

}

TreeNode::TreeNode(const Entity& entity, Ref<HierarchyPanel> panel)
	: m_entity(entity), m_panel(panel)
{
	auto& hierarchy = m_entity.GetComponent<Hierarchy>();
	const auto& children = hierarchy.getChildren();
	for (auto& child : children)
	{
		m_children.push_back(TreeNode(child, m_panel));
	}

	m_title = m_entity.GetComponent<Tag>();
}

void TreeNode::initialize(const Entity& entity, Ref<HierarchyPanel> panel)
{
	m_entity = entity;
	m_panel = panel;

	auto& hierarchy = m_entity.GetComponent<Hierarchy>();
	const auto& children = hierarchy.getChildren();
	m_children.resize(children.size());

	for (size_t i = 0; i < children.size(); i++)
	{
		m_children[i].initialize(children[i], m_panel);
	}

	m_title = m_entity.GetComponent<Tag>();
}

void TreeNode::update()
{
	/*for (size_t i = m_children.size() - 1; i >= 0; i++)
	{
		if (!m_children[i].getEntity().isValid())
			m_children.erase(m_children.begin() + i);
	}

	for (auto& e : m_scene->getCreatedEntities())
	{
		m_treeNodes.push_back(TreeNode(e, shared_from_this()));
	}*/
}

void TreeNode::render()
{
	bool nodeOpen = false;
	ImGuiTreeNodeFlags nodeFlags = 
		ImGuiTreeNodeFlags_OpenOnArrow |
		ImGuiTreeNodeFlags_OpenOnDoubleClick |
		ImGuiTreeNodeFlags_SpanAvailWidth;

	if (m_panel->getSelectedEntityHandle() == m_entity.GetHandle())
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
			e.GetComponent<Hierarchy>().setParent(m_entity);
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
