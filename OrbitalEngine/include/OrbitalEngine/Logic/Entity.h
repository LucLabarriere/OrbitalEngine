#pragma once

#include "OrbitalEngine/Utils.h"
#include "OrbitalEngine/Components/UUID.h"
#include "OrbitalEngine/Components/Tag.h"

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
		template <typename T, typename ...Args> Ref<T> AddNativeScript(Args... args);
		template <typename T> Ref<T> GetNativeScript();

		void ChangeLayer(LayerID layerId);
		void Destroy();

		entt::entity GetHandle() const { return mHandle; }
		LayerID GetLayerID() const { return mLayerId; }
		bool IsValid() const;
		static Entity FromUUID(const UUID& uuid);

		bool operator==(const Entity& e);

	private:
		LayerID mLayerId = 0;
		entt::entity mHandle = entt::null;
	};
}

#ifndef SCENE_H
#include "OrbitalEngine/Logic/Scene.h"
#endif