#include "HierarchyPanel.h"
#include "OrbitalEngine/Logic/Scene.h"
#include "Inspector.h"
#include "Tools.h"

static void renderTreeNode(Entity& entity, Ref<HierarchyPanel> panel)
{
	auto& hierarchy = entity.get<Components::Hierarchy>();
	auto& tag = entity.get<Components::Tag>();
	auto& children = hierarchy.getChildren();

	bool nodeOpen = false;
	ImGuiTreeNodeFlags nodeFlags =
		ImGuiTreeNodeFlags_OpenOnArrow |
		ImGuiTreeNodeFlags_OpenOnDoubleClick |
		ImGuiTreeNodeFlags_SpanAvailWidth;

	if (panel->getSelectedEntityHandle() == entity.getHandle())
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
			e.get<Components::Hierarchy>().setParent(entity);
		}
		ImGui::EndDragDropTarget();
	}

	if (ImGui::IsItemClicked())
	{
		panel->setSelectedEntity(entity);
		Inspector::SetEntity(entity);
	}

	if (nodeOpen)
	{
		for (auto& e : children)
			renderTreeNode(e, panel);

		ImGui::TreePop();
	}
}

HierarchyPanel::HierarchyPanel(Ref<Scene>& scene)
	: m_scene(scene)
{

}

void HierarchyPanel::initialize()
{
	Entity entity = m_scene->getSceneEntity();

	auto& hierarchy = entity.get<Components::Hierarchy>();
	m_sceneChildren = &hierarchy.getChildren();

	m_treeNodes.resize(m_sceneChildren->size());

	for (size_t i = 0; i < m_sceneChildren->size(); i++)
	{
		m_treeNodes[i].initialize((*m_sceneChildren)[i], shared_from_this());
	}
}

void HierarchyPanel::update()
{
	/*for (size_t i = m_treeNodes.size() - 1; i >= 0; i++)
	{
		if (!m_treeNodes[i].getEntity().isValid())
			m_treeNodes.erase(m_treeNodes.begin() + i);
	}

	for (auto& e : m_scene->getCreatedEntities())
	{
		m_treeNodes.push_back(TreeNode(e, shared_from_this()));
	}*/

	for (auto& treeNode : m_treeNodes)
		treeNode.update();
}

void HierarchyPanel::render()
{
	auto texture = TextureManager::Get("Icons").lock();
	Entity entity = m_scene->getSceneEntity();

	auto& hierarchy = entity.get<Components::Hierarchy>();
	m_sceneChildren = &hierarchy.getChildren();

	bool p_open = true;
	ImGui::Begin("Hierarchy Panel", &p_open, ImGuiWindowFlags_MenuBar);

    if (ImGui::BeginMenuBar())
    {
		bool createEntityButton = Tools::RenderIconButton(TextureIconIndex::Plus);

		if (createEntityButton)
			m_scene->createEntity("Entity");		

        ImGui::EndMenuBar();
    }

	renderTreeNode(entity, shared_from_this());

	ImGui::End();
}
