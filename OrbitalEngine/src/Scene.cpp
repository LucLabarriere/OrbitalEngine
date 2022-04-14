#include "OrbitalEngine/Logic/Scene.h"
#include "OrbitalEngine/Graphics/Camera.h"
#include "OrbitalEngine/Logic/Entity.h"

namespace Orbital
{
	Scene::Scene() : m_camera(CreateRef<Camera>())
	{

	}

	void Scene::initialize()
	{
		for (auto& layer : m_layers)
		{
			layer = CreateRef<entt::registry>();
		}

		Entity e = Entity(m_layers[OE_LAST_LAYER]);

		e.add<Components::Tag>(getUniqueTag("Scene"));
		auto& hierarchy = e.add<Components::Hierarchy>(shared_from_this(), e, Entity());

		e.add<LayerID>(OE_LAST_LAYER);
		m_entityHandle = e.getHandle();
	}

	Entity Scene::createEntity(const Components::Tag& tag, LayerID layerId)
	{
		Entity e(m_layers[layerId]);

		e.add<Components::Tag>(getUniqueTag(tag));
		auto& hierarchy = e.add<Components::Hierarchy>(shared_from_this(), e, getSceneEntity());

		e.add<LayerID>(layerId);
		
		return e;
	}

	void Scene::requireDelete(const Entity& entity)
	{
		m_deleteRequired.push_back(entity);
	}

	std::string Scene::getUniqueTag(const std::string& tag, Entity* entity)
	{
		size_t count = 0;

		std::string newTag(tag);
		bool changedName = true;
		entt::entity handle = entt::null;

		if (entity)
			handle = entity->getHandle();


		while (changedName)
		{
			changedName = false;

			for (auto& registry : m_layers)
			{
				auto view = registry->view<Components::Tag>();
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
		}

		return newTag;
	}

	void Scene::renameEntity(Entity& e, const Components::Tag& newTag)
	{
		e.get<Components::Tag>() = getUniqueTag(newTag, &e);
	}

	void Scene::endScene()
	{
		for (auto& entity : m_deleteRequired)
		{
			entity.destroy();
		}
		m_deleteRequired.resize(0);
	}

	Entity Scene::getEntity(const Components::Tag& tag)
	{
		for (auto& registry : m_layers)
		{
			auto view = registry->view<Components::Tag>();

			for (auto entity : view)
			{
				auto& otherTag = view.get<Components::Tag>(entity);
				if (tag == otherTag)
					return Entity(entity, registry);
			}
		}
		OE_RAISE_SIGSEGV("Error, the entity {} does not exist", tag);
	}

	Entity Scene::getSceneEntity()
	{
		return Entity(m_entityHandle, m_layers[OE_LAST_LAYER]);
	}
}