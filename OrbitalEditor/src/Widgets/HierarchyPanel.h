#pragma once

#include "OrbitalEngine/Utils/Misc.h"
#include "OrbitalEngine/Logic/Scene.h"
#include "TreeNode.h"

using namespace OrbitalEngine;

class HierarchyPanel : public std::enable_shared_from_this<HierarchyPanel>
{
public:
	HierarchyPanel(Ref<Scene>& scene);
	
	void initialize();
	void update();
	void render();

	Entity getSelectedEntity() { return m_selectedEntity; };
	entt::entity getSelectedEntityHandle() { return m_selectedEntity.getHandle(); };
	void setSelectedEntity(const entt::entity& selected) { m_selectedEntity = m_scene->getEntity(selected); }

private:
	Ref<Scene> m_scene;
	std::vector<TreeNode> m_treeNodes;
	Entity m_selectedEntity;

	const std::vector<Entity>* m_sceneChildren;
};