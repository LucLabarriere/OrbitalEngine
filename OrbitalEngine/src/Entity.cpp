#include "OrbitalEngine/Logic/Entity.h"
#include "OrbitalEngine/Logic/Scene.h"

namespace Orbital
{
	Entity::Entity()
	{

	}

	void Entity::changeLayer(LayerID layerId)
	{
		OE_NOT_IMPLEMENTED();
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