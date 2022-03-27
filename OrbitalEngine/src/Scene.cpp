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
		e.add<Components::Tag>(getUniqueTag(tag));
		auto& hierarchy = e.add<Components::Hierarchy>(shared_from_this(), e);

		
		if (m_registry->valid(m_entityHandle))
			hierarchy.setParent(getSceneEntity());
		
		return e;
	}

	std::string Scene::getUniqueTag(const std::string& tag, Entity* entity)
	{
		auto view = m_registry->view<Components::Tag>();
		size_t count = 0;

		std::string newTag(tag);
		bool changedName = true;
		entt::entity handle = entt::null;

		if (entity)
			handle = entity->getHandle();


		while (changedName)
		{
			changedName = false;
			for (auto e : view)
			{
				auto& otherTag = view.get<Components::Tag>(e);
				if (newTag == otherTag && e != handle)
				{
					count += 1;
					newTag = tag + "_" + std::to_string(count);
					changedName = true;
				}
			}
		}

		return newTag;
	}

	void Scene::renameEntity(Entity& e, const char* buffer, size_t bufferSize)
	{
		auto view = m_registry->view<Components::Tag>();
		size_t count = 0;

		std::string newTag(buffer);


		for (auto entity : view)
		{
			auto& otherTag = view.get<Components::Tag>(entity);
			if (newTag == otherTag && entity != e.getHandle())
			{
				while (newTag == otherTag)
				{
					count += 1;
					newTag = std::string(buffer) + "_";
					newTag += std::to_string(count);
				}
			}
		}
		e.get<Components::Tag>() = newTag;
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
		OE_RAISE_SIGSEGV("Error, the entity {} does not exist", tag);
	}

	Entity Scene::getEntity(const entt::entity& handle)
	{
		return Entity(handle, shared_from_this());
	}

	Entity Scene::getSceneEntity()
	{
		return Entity(m_entityHandle, shared_from_this());
	}
}