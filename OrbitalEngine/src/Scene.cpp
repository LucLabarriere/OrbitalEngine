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

	void Scene::initialize()
	{
		m_entityHandle = createEntity("Scene").getHandle();
	}

	Entity Scene::createEntity(const Components::Tag& tag)
	{
		Entity e(m_registry->create(), shared_from_this());
		e.add<Components::Tag>(tag);
		auto& hierarchy = e.add<Components::Hierarchy>(shared_from_this(), e);

		
		if (m_registry->valid(m_entityHandle))
			hierarchy.setParent(getSceneEntity());
		
		return e;
	}

	Entity Scene::getEntity(const Components::Tag& tag)
	{
		auto view = m_registry->view<Components::Tag>();

		for (auto entity : view)
		{
			auto& otherTag = view.get<Components::Tag>(entity);
			if (tag == otherTag)
				return Entity(entity, shared_from_this());
		}
	}

	Entity Scene::getSceneEntity()
	{
		return Entity(m_entityHandle, shared_from_this());
	}
}