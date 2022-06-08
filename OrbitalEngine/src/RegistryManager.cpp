#include "OrbitalEngine/Logic.h"
#include "OrbitalEngine/Graphics.h"

#define OE_COPY_COMPONENT(ClassName)\
	{\
	auto var = srcLayers[i]->try_get<ClassName>(e);\
	if (var)\
		dstLayers[i]->emplace<ClassName>(e, *var);\
	}

namespace Orbital
{
	// Initializing
	void RegistryManager::Initialize()
	{
		for (auto& layer : mLayers)
		{
			layer = CreateRef<entt::registry>();
		}

		mMainEntity = Entity(OE_LAST_LAYER, mLayers[OE_LAST_LAYER]->create());

		mMainEntity.AddComponent<UUID>();
		mMainEntity.AddComponent<Tag>(GetUniqueTag("Scene"));
		mMainEntity.AddComponent<NativeScriptManager>();
		auto& hierarchy = mMainEntity.AddComponent<Hierarchy>(mMainEntity, Entity());

		mMainEntity.AddComponent<LayerID>(OE_LAST_LAYER);
	}

	Entity RegistryManager::GetEntity(const Tag& tag)
	{
		for (size_t i = 0; i < mLayers.size(); i++)
		{
			auto& layer = mLayers[i];

			auto view = layer->view<Tag>();

			for (auto entity : view)
			{
				auto& otherTag = view.get<Tag>(entity);

				if (tag == otherTag)
					return Entity(i, entity);
			}
		}

		// TODO test this function in scripts
		OE_RAISE_SIGSEGV("ECS: The entity {} does not exist", tag);
	}

	Entity RegistryManager::GetEntity(const UUID& uuid)
	{
		for (size_t i = 0; i < mLayers.size(); i++)
		{
			auto& layer = mLayers[i];
			auto view = layer->view<UUID>();

			for (auto entity : view)
			{
				auto& otherUUID = view.get<UUID>(entity);

				if (uuid == otherUUID)
					return Entity(i, entity);
			}
		}

		// TODO: test this function in scripts
		OE_RAISE_SIGSEGV("ECS: The entity {} does not exist", (size_t)uuid);
	}

	void RegistryManager::DeleteEntity(const entt::entity& handle, const LayerID& layerId)
	{
		mLayers[layerId]->destroy(handle);
	}

	bool RegistryManager::IsValid(const Entity& entity) const
	{
		return mLayers[entity.GetLayerID()]->valid(entity.GetHandle());
	}

	bool RegistryManager::IsValid(const UUID& uuid) const
	{
		for (size_t i = 0; i < mLayers.size(); i++)
		{
			auto& layer = mLayers[i];
			auto view = layer->view<UUID>();

			for (auto entity : view)
			{
				auto& otherUUID = view.get<UUID>(entity);

				if (uuid == otherUUID)
					return true;
			}
		}

		return false;
	}

	Entity RegistryManager::GetSceneEntity()
	{
		return mMainEntity;
	}

	bool RegistryManager::IsValid(const entt::entity& handle, const LayerID& layerId) const
	{
		return mLayers[layerId]->valid(handle);
	}

	Entity RegistryManager::CreateEntity(const Tag& tag, LayerID layerId)
	{
		Entity e(layerId, mLayers[layerId]->create());

		e.AddComponent<UUID>();
		e.AddComponent<Tag>(GetUniqueTag(tag));
		auto& hierarchy = e.AddComponent<Hierarchy>(e, GetSceneEntity());
		e.AddComponent<NativeScriptManager>();
		e.AddComponent<LayerID>(layerId);
		mCreatedEntities.push_back(e);

		return e;
	}

	Entity RegistryManager::CreateEntity(const Tag& tag, LayerID layerId, const entt::entity& handle)
	{
		Entity e(layerId, mLayers[layerId]->create(handle));

		e.AddComponent<UUID>();
		e.AddComponent<Tag>(GetUniqueTag(tag));
		auto& hierarchy = e.AddComponent<Hierarchy>(e, GetSceneEntity());

		e.AddComponent<NativeScriptManager>();
		e.AddComponent<LayerID>(layerId);
		mCreatedEntities.push_back(e);

		return e;
	}

	Entity RegistryManager::DuplicateEntity(const Entity& e)
	{
		// TODO correct bug when copy pasting a child entity with children /
		auto& tag = e.GetComponent<Tag>();
		auto& layerId = e.GetComponent<LayerID>();
		auto& hiearchy = e.GetComponent<Hierarchy>();
		auto* transform = e.TryGetComponent<Transform>();
		auto* meshRenderer = e.TryGetComponent<MeshRenderer>();
		auto* directionalLight = e.TryGetComponent<DirectionalLight>();
		auto* pointLight = e.TryGetComponent<PointLight>();
		auto* spotLight = e.TryGetComponent<SpotLight>();

		auto newEntity = CreateEntity(tag, layerId);

		if (transform)
		{
			auto& newTransform = newEntity.AddComponent<Transform>(*transform);

			if (meshRenderer)
				newEntity.AddComponent<MeshRenderer>(*meshRenderer, &newTransform);
		}

		if (directionalLight)
			newEntity.AddComponent<DirectionalLight>(*directionalLight);

		if (pointLight)
			newEntity.AddComponent<PointLight>(*pointLight);

		if (spotLight)
			newEntity.AddComponent<SpotLight>(*spotLight);

		newEntity.GetComponent<Hierarchy>().SetParent(hiearchy.GetParent());

		auto& children = hiearchy.GetChildren();

		for (auto& child : children)
		{
			auto newChild = DuplicateEntity(child);
			newChild.GetComponent<Hierarchy>().SetParent(newEntity);
		}

		return newEntity;
	}

	void RegistryManager::RequireDelete(const Entity& entity)
	{
		mDeleteRequired.push_back(entity);
	}

	void RegistryManager::RenameEntity(Entity& e, const Tag& newTag)
	{
		e.GetComponent<Tag>() = GetUniqueTag(newTag, &e);
	}

	std::string RegistryManager::GetUniqueTag(const std::string& tag, Entity* entity)
	{
		// TODO: check this method, why do we use Entity* ?
		size_t count = 0;

		std::string newTag(tag);
		bool changedName = true;
		entt::entity handle = entt::null;

		if (entity)
			handle = entity->GetHandle();

		while (changedName)
		{
			changedName = false;

			for (auto& registry : mLayers)
			{
				auto view = registry->view<Tag>();
				for (auto e : view)
				{
					auto& otherTag = view.get<Tag>(e);
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
}