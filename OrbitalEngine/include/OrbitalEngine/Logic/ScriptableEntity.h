#pragma once

#include "OrbitalEngine/Logic/Scene.h"
#include "OrbitalEngine/Events.h"
#include "OrbitalEngine/Utils.h"

namespace Orbital
{
	class ScriptableEntity : public Entity
	{
	public:
		ScriptableEntity(const Entity& e) : Entity(e) { onLoad(); }
		virtual ~ScriptableEntity() { }

		virtual void onLoad() { };
		virtual void onStart() { };
		virtual void onUpdate(Time t) { };
		virtual void onExit() { };

		virtual bool onKeyPressed(const KeyPressedEvent& e) { return false; }
		virtual bool onKeyReleased(const KeyReleasedEvent& e) { return false; }
		virtual bool onMouseMoved(const MouseMovedEvent& e) { return false; }
		virtual bool onMouseScrolled(const MouseScrolledEvent& e) { return false; }
		virtual bool onMouseButtonPressed(const MouseButtonPressedEvent& e) { return false; }
		virtual bool onMouseButtonReleased(const MouseButtonReleasedEvent& e) { return false; }
		virtual bool onWindowResized(const WindowResizedEvent& e) { return false; }

		void setUpdating(bool value) { m_updating = value; }
		bool isUpdating() const { return m_updating; }

	private:
		bool m_updating = true;
	};
}