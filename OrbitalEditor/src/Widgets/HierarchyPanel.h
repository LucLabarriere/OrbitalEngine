#pragma once

#include "OrbitalEngine/Utils/Misc.h"
#include "OrbitalEngine/Logic/Scene.h"
#include "TreeNode.h"

using namespace OrbitalEngine;

class HierarchyPanel
{
public:
	HierarchyPanel(Ref<Scene>& scene);

	void render();

private:
	Ref<Scene> m_scene;
	std::vector<TreeNode> m_treeNodes;
};