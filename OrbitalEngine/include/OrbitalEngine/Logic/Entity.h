#pragma once
#include "OrbitalEngine/Logic/Scene.h"

namespace OrbitalEngine
{
	class Entity
	{
	public:
		template <class T, typename ...Args>
		void add(Args... args)
		{
			m_scene->getRegistry()->emplace<T>(m_id, args...);
		}

	private:
		Entity(entt::entity id, Scene* scene)
			: m_id(id), m_scene(scene)
		{

		}

	private:
		friend Scene;

		entt::entity m_id;
		Scene* m_scene;
	};
}
