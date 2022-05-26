#include "OrbitalEngine/Logic/Entity.h"
#include "OrbitalEngine/Logic/Scene.h"

namespace Orbital
{
	Entity::Entity()
	{

	}

	Entity::Entity(const Entity& e)
	{
		m_registry = e.m_registry;
		m_handle = e.m_handle;
	}

	void Entity::changeLayer(LayerID layerId)
	{
		OE_NOT_IMPLEMENTED();
	}

	void Entity::destroy()
	{
		auto& hierarchy = get<Components::Hierarchy>();
		auto& children = hierarchy.getChildren();

		for (int i = children.size() - 1; i >= 0; i--)
		{
			children[i].destroy();
		}
		hierarchy.getParent().get<Components::Hierarchy>().removeChild(*this);

		auto mr = tryGet<Components::MeshRenderer>();
		if (mr) mr->destroy();

		m_registry->destroy(m_handle);
	}

	Entity::Entity(Ref<entt::registry>& registry)
		: m_registry(registry), m_handle(registry->create())
	{

	}

	Entity::Entity(entt::entity handle, Ref<entt::registry>& registry)
		: m_registry(registry), m_handle(handle)
	{

	}

	Entity::~Entity()
	{

	}
}