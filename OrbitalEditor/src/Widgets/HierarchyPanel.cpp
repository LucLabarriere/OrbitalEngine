#include "HierarchyPanel.h"
#include "OrbitalEngine/Logic/Scene.h"

HierarchyPanel::HierarchyPanel(Ref<Scene>& scene)
	: m_scene(scene)
{
	Entity entity = m_scene->getSceneEntity();
	
	auto& hierarchy = entity.get<Components::Hierarchy>();
	m_sceneChildren = &hierarchy.getChildren();

	update();
}

void HierarchyPanel::update()
{
	m_treeNodes.clear();
	for (auto& child : *m_sceneChildren)
	{
		m_treeNodes.push_back(child);
	}
}

void HierarchyPanel::render()
{
	ImGui::Begin("Hierarchy Panel");
	for (auto& node : m_treeNodes)
		node.render();
	ImGui::End();
}
