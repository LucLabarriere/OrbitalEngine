#pragma once

#include "OrbitalEngine/Utils/Logger.h"
#include "OrbitalEngine/Logic.h"
#include "OrbitalEngine/Components.h"

using namespace Orbital;

class HierarchyPanel;

class TreeNode
{
public:
	TreeNode();
	TreeNode(const Entity& entity, Ref<HierarchyPanel> panel);
	void initialize(const Entity& entity, Ref<HierarchyPanel> panel);
	void update();
	const Entity& getEntity() const { return m_entity; }

	void render();

private:
	Entity m_entity;
	std::vector<TreeNode> m_children;
	std::string m_title;
	Ref<HierarchyPanel> m_panel;
};
