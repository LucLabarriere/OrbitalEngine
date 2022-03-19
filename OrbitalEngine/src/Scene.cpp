#include "OrbitalEngine/Logic/Scene.h"
#include "OrbitalEngine/Graphics/Camera.h"
#include "OrbitalEngine/Logic/Entity.h"

namespace OrbitalEngine
{
	Scene::Scene()
		: m_camera(CreateRef<Camera>())
		, m_registry(CreateRef<entt::registry>())
	{

	}

	Entity Scene::createEntity()
	{
		return Entity(m_registry->create(), this);
	}
}