#pragma once

#include "OrbitalEngine/Graphics/Camera.h"
#include "OrbitalEngine/Components.h"

namespace Orbital
{
	class Entity;

	class Scene : public std::enable_shared_from_this<Scene>
	{
	public:
		Scene();

		void initialize();
		Entity createEntity(const Components::Tag& tag, LayerID layerId = 0);
		std::string getUniqueTag(const std::string& tag, Entity* entity = nullptr);
		void renameEntity(Entity& e, const Components::Tag& newTag);

		Entity getEntity(const Components::Tag& tag);
		Ref<Camera>& getCamera() { return m_camera; }
		Ref<entt::registry>& getRegistry(LayerID layerId = 0) { return m_layers[layerId]; }
		Entity getSceneEntity();

	private:
		Ref<Camera> m_camera;
		std::array<Ref<entt::registry>, OE_LAST_LAYER + 1> m_layers;
		entt::entity m_entityHandle = entt::null;
	};
}