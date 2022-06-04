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
	void Initialize(const Entity& entity, Ref<HierarchyPanel> panel);
	void Update();
	const Entity& GetEntity() const { return mEntity; }

	void Render();

private:
	Entity mEntity;
	std::vector<TreeNode> mChildren;
	std::string mTitle;
	Ref<HierarchyPanel> mPanel;
};
