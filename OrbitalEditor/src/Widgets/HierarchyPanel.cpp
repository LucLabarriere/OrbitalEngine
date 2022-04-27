#include "HierarchyPanel.h"
#include "OrbitalEngine/Logic/Scene.h"

HierarchyPanel::HierarchyPanel(Ref<Scene>& scene)
	: m_scene(scene)
{

}

void HierarchyPanel::initialize()
{
	Entity entity = m_scene->getSceneEntity();

	auto& hierarchy = entity.get<Components::Hierarchy>();
	m_sceneChildren = &hierarchy.getChildren();
	update();
}

void HierarchyPanel::update()
{
	m_treeNodes.resize(m_sceneChildren->size());
	
	for (size_t i = 0; i < m_sceneChildren->size(); i++)
	{
		m_treeNodes[i].initialize((*m_sceneChildren)[i], shared_from_this());
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
