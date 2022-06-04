#pragma once

#include "OrbitalEngine/Utils.h"
#include "OrbitalEngine/Components/Tag.h"
#include "OrbitalEngine/Components/UUID.h"
#include "OrbitalEngine/Logic/NativeScriptManager.h"

namespace Orbital
{
	class Camera;
	class Scene;
	class ScriptableEntity;

	class Entity
	{
	public:
		Entity();
		Entity(const Entity& e);
		Entity(const LayerID& layerId, const entt::entity& handle);

		template <typename T> bool HasComponent() const;
		template <typename T> T& GetComponent() const;
		template <typename T> T* TryGetComponent() const;
		template <typename T> void RemoveComponent() const;
		template <typename T, typename... Args> T& AddComponent(Args... args);

		void ChangeLayer(LayerID layerId);
		void Destroy();
		static void SetSceneReference(Scene** scene) { sActiveScene = scene; }

		entt::entity GetHandle() const { return mHandle; }
		LayerID GetLayerID() const { return mLayerId; }
		bool IsValid() const;

		bool operator==(const Entity& e);

	private:
		static inline Scene** sActiveScene;
		LayerID mLayerId = 0;
		entt::entity mHandle = entt::null;
	};

	class Scene
	{
	public:
		// Initializing
		Scene();
		void Initialize();
		Scene Copy(Scene& newScene);

		// Working on the ECS
		Entity GetEntity(const Tag& tag);
		Entity GetEntity(const UUID& uuid);
		void DeleteEntity(const entt::entity& handle, const LayerID& layerId);
		Entity GetSceneEntity();
		bool IsValid(const entt::entity& handle, const LayerID& layerId) const;
		Entity CreateEntity(const Tag& tag, LayerID layerId = 0);
		Entity CreateEntity(const Tag& tag, LayerID layerId, const entt::entity& handle);
		Entity DuplicateEntity(const Entity& e);
		void RequireDelete(const Entity& entity);
		void RenameEntity(Entity& e, const Tag& newTag);
		Ref<entt::registry>& GetRegistry(LayerID layerId = 0) { return mLayers[layerId]; }
		void SetMainCamera(const Entity& camera) { mMainCamera = camera; }
		void SetUpdating(bool value);

		// Rendering
		void Begin();
		void End();
		void Render();
		void OnStart();
		void OnLoad();
		void OnExit();
		void OnUpdate(Time dt);

		// Tools
		void SetAspectRatio(float aspectRatio);
		void Serialize();
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
			if constexpr (std::is_base_of<ScriptableEntity, T>::value)
			{
				T& script = mLayers[layerId]->emplace<T>(handle, Entity(layerId, handle), args...);
				NativeScriptManager::Register(&script);
				return script;
			}
			else
			{
				return mLayers[layerId]->emplace<T>(handle, args...);
			}
		}

		template <typename T>
		void LoadScript() const
		{
			for (auto& layer : mLayers)
			{
				auto view = layer->view<T>();

				for (auto entity : view)
				{
					auto& t = view.get<T>(entity);
					t.onLoad();
				}
			}
		}

		template <typename T>
		void StartScript() const
		{
			for (auto& layer : mLayers)
			{
				auto view = layer->view<T>();

				for (auto entity : view)
				{
					auto& t = view.get<T>(entity);
					t.onStart();
				}
			}
		}

		template <typename T>
		void ExitScript() const
		{
			for (auto& layer : mLayers)
			{
				auto view = layer->view<T>();

				for (auto entity : view)
				{
					auto& t = view.get<T>(entity);
					t.onExit();
				}
			}
		}

		template <typename T>
		void UpdateScript(Time dt) const
		{
			for (auto& layer : mLayers)
			{
				auto view = layer->view<T>();

				for (auto entity : view)
				{
					auto& t = view.get<T>(entity);
					if (t.isUpdating())
						t.onUpdate(dt);
				}
			}
		}

		template <typename T>
		void SetUpdating(bool value)
		{
			for (auto& layer : mLayers)
			{
				auto view = layer->view<T>();

				for (auto entity : view)
				{
					auto& t = view.get<T>(entity);
					t.setUpdating(value);
				}
			}
		}

		private:
			std::array<Ref<entt::registry>, OE_LAST_LAYER + 1> mLayers;
			Entity mMainEntity;
			Entity mMainCamera;
			std::vector<Entity> mDeleteRequired;
			std::vector<Entity> mCreatedEntities;
	};

	template <typename T>
	bool Entity::HasComponent() const
	{
		return (*sActiveScene)->HasComponent<T>(mHandle, mLayerId);
	}

	template <typename T>
	T& Entity::GetComponent() const
	{
		return (*sActiveScene)->GetComponent<T>(mHandle, mLayerId);
	}

	template <typename T>
	T* Entity::TryGetComponent() const
	{
		return (*sActiveScene)->TryGetComponent<T>(mHandle, mLayerId);
	}

	template <typename T>
	void Entity::RemoveComponent() const
	{
		return (*sActiveScene)->RemoveComponent<T>(mHandle, mLayerId);
	}

	template <typename T, typename... Args>
	T& Entity::AddComponent(Args... args)
	{
		return (*sActiveScene)->AddComponent<T>(mHandle, mLayerId, args...);
	}
}
