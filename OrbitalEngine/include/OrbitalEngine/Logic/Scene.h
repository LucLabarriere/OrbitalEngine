#pragma once

#include "OrbitalEngine/Graphics/Camera.h"
#include "OrbitalEngine/Components.h"

namespace OrbitalEngine
{
	class Entity;

	class Scene : public std::enable_shared_from_this<Scene>
	{
	public:
		Scene();

		void initialize();
		Entity createEntity(const Components::Tag& tag);
		Entity getEntity(const Components::Tag& tag);

		Ref<Camera>& getCamera() { return m_camera; }
		Ref<entt::registry>& getRegistry() { return m_registry; }
		Entity getSceneEntity();

	private:
		Ref<Camera> m_camera;
		Ref<entt::registry> m_registry;
		entt::entity m_entityHandle;
	};
}