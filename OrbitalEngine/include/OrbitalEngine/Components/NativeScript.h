#pragma once

#include "OrbitalEngine/Utils/Time.h"
#include "OrbitalEngine/Logic/Entity.h"

namespace Orbital
{
	class Scriptable: public Entity
	{
	public:
		Scriptable(const Entity& e) : Entity(e) { }
		virtual ~Scriptable() { }

		virtual void onLoad() = 0;
		virtual void onStart() = 0;
		virtual void onUpdate(Time t) = 0;
	};

	namespace Components
	{
		template<typename T>
		class NativeScript
		{
		public:
			NativeScript<T>(const Entity& e)
			{
				m_instance = CreateRef<T>(e);
			}
			NativeScript<T>(Ref<T>& instance)
			{
				m_instance = instance;
			}

			Ref<T> getInstance() { return m_instance; }

		private:
			Ref<T> m_instance;
		};
	}
}