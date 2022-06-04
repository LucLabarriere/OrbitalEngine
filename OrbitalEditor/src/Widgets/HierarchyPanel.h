#pragma once

#include "OrbitalEngine/Utils/Misc.h"
#include "OrbitalEngine/Logic/Scene.h"
#include "TreeNode.h"
#include "Widget.h"

using namespace Orbital;

class HierarchyPanel : public std::enable_shared_from_this<HierarchyPanel>, Widget
{
public:
	HierarchyPanel();
	
	void initialize();
	void update();
	void render();

	Entity& getSelectedEntity() { return m_selectedEntity; };
	entt::entity getSelectedEntityHandle() { return m_selectedEntity.GetHandle(); };
	void setSelectedEntity(const Entity& entity) { m_selectedEntity = entity; }

private:
	std::vector<TreeNode> m_treeNodes;
	Entity m_selectedEntity;

	const std::vector<Entity>* m_sceneChildren;
};