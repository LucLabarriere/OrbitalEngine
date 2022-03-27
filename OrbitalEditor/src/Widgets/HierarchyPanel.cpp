#include "HierarchyPanel.h"
#include "OrbitalEngine/Logic/Scene.h"

HierarchyPanel::HierarchyPanel(Ref<Scene>& scene)
	: m_scene(scene)
{
	Entity entity = m_scene->getSceneEntity();
	
	auto& hierarchy = entity.get<Components::Hierarchy>();
	m_sceneChildren = &hierarchy.getChildren();
}

void HierarchyPanel::initialize()
{
	update();
}

void HierarchyPanel::update()
{
	m_treeNodes.clear();
	for (auto& child : *m_sceneChildren)
	{
		m_treeNodes.push_back(TreeNode(child, shared_from_this()));
	}
}

void HierarchyPanel::render()
{
	bool p_open = true;
	ImGui::Begin("Hierarchy Panel", &p_open, ImGuiWindowFlags_MenuBar);


    if (ImGui::BeginMenuBar())
    {
		if (ImGui::Button("+"))
		{
			m_scene->createEntity("Entity");
		}
        ImGui::EndMenuBar();
    }

	for (auto& node : m_treeNodes)
		node.render();

	ImGui::End();
}
