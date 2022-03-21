#pragma once

#include "OrbitalEngine/Utils/Misc.h"

namespace OrbitalEngine
{
	class Scene;

	class Entity
	{
	public:
		~Entity();

		template <class T, typename ...Args>
		T& add(Args... args)
		{
			return m_registry->emplace<T>(m_handle, args...);
		}

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

		entt::entity getHandle() const { return m_handle; }

		bool operator==(const Entity& e) { return (e.getHandle() == m_handle) ? true : false; }
	
	private:
		Entity(entt::entity handle, Ref<Scene> scene);

	private:
		friend Scene;

		entt::entity m_handle;
		WeakRef<Scene> m_scene;
		Ref<entt::registry> m_registry;
	};
}
