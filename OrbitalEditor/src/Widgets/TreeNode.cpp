#include "TreeNode.h"
#include "HierarchyPanel.h"
#include "Inspector.h"

TreeNode::TreeNode()
	: mEntity(), mPanel(nullptr)
{

}

TreeNode::TreeNode(const Entity& entity, Ref<HierarchyPanel> panel)
	: mEntity(entity), mPanel(panel)
{
	auto& hierarchy = mEntity.GetComponent<Hierarchy>();
	const auto& children = hierarchy.GetChildren();
	for (auto& child : children)
	{
		mChildren.push_back(TreeNode(child, mPanel));
	}

	mTitle = mEntity.GetComponent<Tag>();
}

void TreeNode::Initialize(const Entity& entity, Ref<HierarchyPanel> panel)
{
	mEntity = entity;
	mPanel = panel;

	auto& hierarchy = mEntity.GetComponent<Hierarchy>();
	const auto& children = hierarchy.GetChildren();
	mChildren.resize(children.size());

	for (size_t i = 0; i < children.size(); i++)
	{
		mChildren[i].Initialize(children[i], mPanel);
	}

	mTitle = mEntity.GetComponent<Tag>();
}

void TreeNode::Update()
{
	/*for (size_t i = mChildren.size() - 1; i >= 0; i++)
	{
		if (!mChildren[i].GetEntity().isValid())
			mChildren.erase(mChildren.begin() + i);
	}

	for (auto& e : mScene->getCreatedEntities())
	{
		mTreeNodes.push_back(TreeNode(e, shared_from_this()));
	}*/
}

void TreeNode::Render()
{
	bool nodeOpen = false;
	ImGuiTreeNodeFlags nodeFlags = 
		ImGuiTreeNodeFlags_OpenOnArrow |
		ImGuiTreeNodeFlags_OpenOnDoubleClick |
		ImGuiTreeNodeFlags_SpanAvailWidth;

	if (mPanel->GetSelectedEntityHandle() == mEntity.GetHandle())
	{
		nodeFlags |= ImGuiTreeNodeFlags_Selected;
	}

	if (mChildren.size() == 0)
	{
		nodeFlags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
		ImGui::TreeNodeEx(mTitle.c_str(), nodeFlags);
	}
	else
	{
		nodeOpen = ImGui::TreeNodeEx(mTitle.c_str(), nodeFlags);
	}

	// Source
	if (ImGui::BeginDragDropSource())
	{
		ImGui::SetDragDropPayload("TreeNode", (const void*)&mEntity, sizeof(mEntity));
		ImGui::EndDragDropSource();
	}

	// Target
	if (ImGui::BeginDragDropTarget())
	{
		const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("TreeNode");
		if (payload)
		{
			Entity e = *static_cast<Entity*>(payload->Data);
			e.GetComponent<Hierarchy>().SetParent(mEntity);
		}
		ImGui::EndDragDropTarget();
	}

	if (ImGui::IsItemClicked())
	{
		mPanel->SetSelectedEntity(mEntity);
		Inspector::SetEntity(mEntity);
	}

	if (nodeOpen)
	{
		for (auto& node : mChildren)
			node.Render();

		ImGui::TreePop();
	}
}