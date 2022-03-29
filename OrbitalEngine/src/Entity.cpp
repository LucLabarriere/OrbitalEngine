#include "OrbitalEngine/Logic/Entity.h"
#include "OrbitalEngine/Logic/Scene.h"

namespace OrbitalEngine
{
	Entity::Entity()
	{

	}

	Entity::~Entity()
	{
		m_registry.reset();
		m_scene.reset();
	}

	Entity::Entity(entt::entity handle, Ref<Scene> scene)
		: m_handle(handle), m_scene(scene), m_registry(scene->getRegistry())
	{

	}
}