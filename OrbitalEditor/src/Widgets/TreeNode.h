#pragma once

#include "OrbitalEngine/Utils/Logger.h"
#include "OrbitalEngine/Logic/Entity.h"
#include "OrbitalEngine/Components.h"

using namespace OrbitalEngine;

class TreeNode
{
public:
	TreeNode(const Entity& entity)
		: m_entity(entity)
	{
		auto& hierarchy = m_entity.get<Components::Hierarchy>();
		const auto& children = hierarchy.getChildren();
		for (auto& child : children)
		{
			m_children.push_back(child);
		}
	}

	void render()
	{
		if (ImGui::TreeNode(m_entity.get<Components::Tag>().c_str()))
		{
			for (auto& node : m_children)
				node.render();
			ImGui::TreePop();
		}
	}

private:
	Entity m_entity;
	std::vector<TreeNode> m_children;
};
