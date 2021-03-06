#pragma once

#include "Entity.h"

namespace Orbital
{
	class RegistryManager
	{
	public:
		virtual void Initialize();
		Entity GetEntity(const Tag& tag);
		Entity GetEntity(const UUID& uuid);
		Entity GetSceneEntity();
		void DeleteEntity(const entt::entity& handle, const LayerID& layerId);
		bool IsValid(const Entity& entity) const;
		bool IsValid(const UUID& uuid) const;
		bool IsValid(const entt::entity& handle, const LayerID& layerId) const;
		Entity CreateEntity(const Tag& tag, LayerID layerId = 0);
		Entity CreateEntity(const Tag& tag, LayerID layerId, const entt::entity& handle);
		Entity DuplicateEntity(const Entity& e);
		void RequireDelete(const Entity& entity);
		void RenameEntity(Entity& e, const Tag& newTag);
		Ref<entt::registry>& GetRegistry(LayerID layerId = 0) { return mLayers[layerId]; }

		std::string GetUniqueTag(const std::string& tag, Entity* entity = nullptr);
		bool EntityDeleted() { return mDeleteRequired.size() == 0 ? false : true; }
		const std::vector<Entity> GetCreatedEntities() const { return mCreatedEntities; }

		// Components handling
		template <typename T>
		bool HasComponent(const entt::entity& handle, const LayerID& layerId) const
		{
			return mLayers[layerId]->try_get<T>(handle) ? true : false;
		}

		template <typename T>
		T& GetComponent(const entt::entity& handle, const LayerID& layerId) const
		{
			return mLayers[layerId]->get<T>(handle);
		}

		template <typename T>
		T* TryGetComponent(const entt::entity& handle, const LayerID& layerId) const
		{
			return mLayers[layerId]->try_get<T>(handle);
		}

		template <typename T>
		void RemoveComponent(const entt::entity& handle, const LayerID& layerId) const
		{
			mLayers[layerId]->remove<T>(handle);
		}

		template <typename T, typename ...Args>
		T& AddComponent(const entt::entity& handle, const LayerID& layerId, Args... args)
		{
			return mLayers[layerId]->emplace<T>(handle, args...);
		}

		template <typename T, typename ...Args>
		Ref<T> AddNativeScript(const Entity& e, Args... args);

		template <typename T>
		Ref<T> GetNativeScript(const entt::entity& handle, const LayerID& layerId);

		template <typename T>
		void SetUpdating(bool value)
		{
			for (auto& layer : mLayers)
			{
				auto view = layer->view<T>();

				for (auto entity : view)
				{
					auto& t = view.get<T>(entity);
					t.SetUpdating(value);
				}
			}
		}

	protected:
		std::array<Ref<entt::registry>, OE_LAST_LAYER + 1> mLayers;
		std::vector<Entity> mDeleteRequired;
		std::vector<Entity> mCreatedEntities;
		Entity mMainEntity;
	};
}