#include "OrbitalEngine/Components/Hierarchy.h"
#include "OrbitalEngine/Logic/Scene.h"

namespace Orbital
{
	Hierarchy::Hierarchy(const Entity& entity, const Entity& parent)
		: m_entity(entity), m_parent(parent)
	{
		if (m_parent.IsValid())
			m_parent.GetComponent<Hierarchy>().addChild(m_entity);
	}

	Hierarchy::~Hierarchy()
	{

	}

	void Hierarchy::setParent(const Entity& parent)
	{
		// Removing former parent
		auto& parentHierarchy = m_parent.GetComponent<Hierarchy>();
		parentHierarchy.removeChild(m_entity);

		// Setting new parent
		m_parent = Entity(parent);
		m_parent.GetComponent<Hierarchy>().addChild(m_entity);
	}

	void Hierarchy::removeChild(const Entity& entity)
	{
		for (size_t i = 0; i < m_children.size(); i++)
			if (m_children[i].GetComponent<UUID>() == entity.GetComponent<UUID>())
				m_children.erase(m_children.begin() + i);
	}

	Entity& Hierarchy::getParent()
	{
		return m_parent;
	}

	std::vector<Entity>& Hierarchy::getChildren()
	{
		return m_children;
	}

	std::vector<Entity>::iterator Hierarchy::begin()
	{
		return m_children.begin();
	}

	std::vector<Entity>::iterator Hierarchy::end()
	{
		return m_children.end();
	}

	void Hierarchy::addChild(const Entity& child)
	{
		m_children.push_back(child);
	}
}