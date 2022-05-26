#pragma once

#include "OrbitalEngine/Utils/Misc.h"

namespace Orbital
{
	class Scene;

	class Entity
	{
	public:
		Entity();
		Entity(const Entity& e);
		~Entity();

		template <class T, typename ...Args>
		T& add(Args... args)
		{
			return m_registry->emplace<T>(m_handle, args...);
		}

		/*T& addScript()
		{
			return add<Components::NativeScript<T>>(NativeScriptManager::Create<T>(e));
		}*/

		template <class T>
		bool has()
		{
			return (m_registry->try_get<T>(m_handle) != nullptr) ? true : false;
		}

		template <class T>
		T& get()
		{
			return m_registry->get<T>(m_handle);
		}

		template <class T>
		T* tryGet()
		{
			return m_registry->try_get<T>(m_handle);
		}

		template <class T>
		void remove()
		{
			m_registry->remove<T>(m_handle);
		}
		void changeLayer(LayerID layerId);

		void destroy();

		entt::entity getHandle() const { return m_handle; }
		bool isValid() const { return m_handle != entt::null and m_registry->valid(m_handle); }

		bool operator==(const Entity& e) { return (e.getHandle() == m_handle) ? true : false; }

	protected:
		Entity(Ref<entt::registry>& registry);
		Entity(entt::entity handle, Ref<entt::registry>& registry);

	private:
		friend Scene;

		Ref<entt::registry> m_registry;
		entt::entity m_handle = entt::null;
	};
}
