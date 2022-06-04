#pragma once

#include "OrbitalEngine/Utils.h"

namespace Orbital
{
	class Scene;

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
}

#ifndef SCENE_H
#include "OrbitalEngine/Logic/Scene.h"
#endif