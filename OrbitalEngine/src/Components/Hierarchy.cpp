#include "OrbitalEngine/Components/Hierarchy.h"
#include "OrbitalEngine/Logic/Scene.h"
#include "OrbitalEngine/Logic/Entity.h"

namespace OrbitalEngine
{
	namespace Components
	{
		Hierarchy::Hierarchy(Ref<Scene>& scene, const Entity& entity)
			: m_scene(scene), m_entity(entity), m_parent(nullptr)
		{

		}

		Hierarchy::~Hierarchy()
		{
			if (m_parent != nullptr)
			{
				delete m_parent;
				m_parent = nullptr;
			}
		}

		void Hierarchy::setParent(const Entity& parent)
		{
			// Removing former parent
			if (m_parent != nullptr)
			{
				auto& parentHierarchy = m_parent->get<Components::Hierarchy>();
				parentHierarchy.removeChild(m_entity);
			}

			// Setting new parent
			m_parent = new Entity(parent);
			m_parent->get<Components::Hierarchy>().addChild(m_entity);
		}

		void Hierarchy::removeChild(const Entity& entity)
		{
			for (size_t i = 0; i < m_children.size(); i++)
				if (m_children[i] == entity)
					m_children.erase(m_children.begin() + i);
		}

		const Entity& Hierarchy::getParent() const
		{
			return *m_parent;
		}

		const std::vector<Entity>& Hierarchy::getChildren() const
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
}