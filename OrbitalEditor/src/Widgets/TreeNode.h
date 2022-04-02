#pragma once

#include "OrbitalEngine/Utils/Logger.h"
#include "OrbitalEngine/Logic/Entity.h"
#include "OrbitalEngine/Components.h"

using namespace Orbital;

class HierarchyPanel;

class TreeNode
{
public:
	TreeNode(const Entity& entity, Ref<HierarchyPanel> panel);

	void render();

private:
	Entity m_entity;
	std::vector<TreeNode> m_children;
	std::string m_title;
	Ref<HierarchyPanel> m_panel;
};
