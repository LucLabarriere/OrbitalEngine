#pragma once

#include "OrbitalEngine/Graphics/Camera.h"

namespace OrbitalEngine
{
	class Entity;

	class Scene
	{
	public:
		Scene();

		Ref<Camera>& getCamera() { return m_camera; }
		Ref<entt::registry>& getRegistry() { return m_registry; }
		Entity createEntity();

	private:
		Ref<Camera> m_camera;
		Ref<entt::registry> m_registry;
	};
}