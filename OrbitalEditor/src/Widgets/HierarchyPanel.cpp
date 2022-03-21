#include "HierarchyPanel.h"
#include "OrbitalEngine/Logic/Scene.h"

HierarchyPanel::HierarchyPanel(Ref<Scene>& scene)
	: m_scene(scene)
{
	Entity entity = m_scene->getSceneEntity();
	
	auto& hierarchy = entity.get<Components::Hierarchy>();
	const auto& children = hierarchy.getChildren();

	for (auto& child : children)
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
