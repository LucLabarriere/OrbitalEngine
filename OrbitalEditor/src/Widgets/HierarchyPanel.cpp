#include "HierarchyPanel.h"
#include "OrbitalEngine/Logic/Scene.h"
#include "Inspector.h"
#include "Tools.h"

static void renderTreeNode(Entity& entity, Ref<HierarchyPanel> panel)
{
	auto& hierarchy = entity.GetComponent<Hierarchy>();
	auto& tag = entity.GetComponent<Tag>();
	auto& children = hierarchy.GetChildren();

	bool nodeOpen = false;
	ImGuiTreeNodeFlags nodeFlags =
		ImGuiTreeNodeFlags_OpenOnArrow |
		ImGuiTreeNodeFlags_OpenOnDoubleClick |
		ImGuiTreeNodeFlags_SpanAvailWidth;

	if (panel->GetSelectedEntityHandle() == entity.GetHandle())
	{
		nodeFlags |= ImGuiTreeNodeFlags_Selected;
	}

	if (children.size() == 0)
	{
		nodeFlags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
		ImGui::TreeNodeEx(tag.c_str(), nodeFlags);
	}
	else
	{
		nodeOpen = ImGui::TreeNodeEx(tag.c_str(), nodeFlags);
	}

	// Source
	if (ImGui::BeginDragDropSource())
	{
		ImGui::SetDragDropPayload("TreeNode", (const void*)&entity, sizeof(entity));
		ImGui::EndDragDropSource();
	}

	// Target
	if (ImGui::BeginDragDropTarget())
	{
		const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("TreeNode");
		if (payload)
		{
			Entity e = *static_cast<Entity*>(payload->Data);
			e.GetComponent<Hierarchy>().SetParent(entity);
		}
		ImGui::EndDragDropTarget();
	}

	if (ImGui::IsItemClicked())
	{
		panel->SetSelectedEntity(entity);
		Inspector::SetEntity(entity);
	}

	if (nodeOpen)
	{
		for (auto& e : children)
			renderTreeNode(e, panel);

		ImGui::TreePop();
	}
}

HierarchyPanel::HierarchyPanel()
{

}

void HierarchyPanel::Initialize()
{
	Entity entity = (*sActiveScene)->GetSceneEntity();

	auto& hierarchy = entity.GetComponent<Hierarchy>();
	mSceneChildren = &hierarchy.GetChildren();

	mTreeNodes.resize(mSceneChildren->size());

	for (size_t i = 0; i < mSceneChildren->size(); i++)
	{
		mTreeNodes[i].Initialize((*mSceneChildren)[i], shared_from_this());
	}
}

void HierarchyPanel::Update()
{
	/*for (size_t i = mTreeNodes.size() - 1; i >= 0; i++)
	{
		if (!mTreeNodes[i].GetEntity().isValid())
			mTreeNodes.erase(mTreeNodes.begin() + i);
	}

	for (auto& e : mScene->getCreatedEntities())
	{
		mTreeNodes.push_back(TreeNode(e, shared_from_this()));
	}*/

	for (auto& treeNode : mTreeNodes)
		treeNode.Update();
}

void HierarchyPanel::Render()
{
	auto texture = TextureManager::Get("Icons").lock();
	Entity entity = (*sActiveScene)->GetSceneEntity();

	auto& hierarchy = entity.GetComponent<Hierarchy>();
	mSceneChildren = &hierarchy.GetChildren();

	bool p_open = true;
	ImGui::Begin("Hierarchy Panel", &p_open, ImGuiWindowFlags_MenuBar);

    if (ImGui::BeginMenuBar())
    {
		bool createEntityButton = Tools::RenderIconButton(TextureIconIndex::Plus);

		if (createEntityButton)
			(*sActiveScene)->CreateEntity("Entity");

        ImGui::EndMenuBar();
    }

	renderTreeNode(entity, shared_from_this());

	ImGui::End();
}
