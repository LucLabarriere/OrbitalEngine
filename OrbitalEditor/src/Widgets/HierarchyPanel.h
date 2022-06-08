#pragma once

#include "OrbitalEngine/Utils/Misc.h"
#include "OrbitalEngine/Logic/Scene.h"
#include "TreeNode.h"
#include "Widget.h"
#include <imgui.h>

using namespace Orbital;

class HierarchyPanel : public std::enable_shared_from_this<HierarchyPanel>
{
public:
	HierarchyPanel();
	
	void Initialize();
	void Update();
	void Render();

	Entity& GetSelectedEntity() { return mSelectedEntity; };
	entt::entity GetSelectedEntityHandle() { return mSelectedEntity.GetHandle(); };
	void SetSelectedEntity(const Entity& entity) { mSelectedEntity = entity; }

private:
	std::vector<TreeNode> mTreeNodes;
	Entity mSelectedEntity;

	const std::vector<Entity>* mSceneChildren;
};