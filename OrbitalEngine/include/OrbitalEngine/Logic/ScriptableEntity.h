#pragma once

#include "OrbitalEngine/Logic/Scene.h"
#include "OrbitalEngine/Events.h"
#include "OrbitalEngine/Utils.h"

namespace Orbital
{
	class ScriptableEntity : public Entity
	{
	public:
		ScriptableEntity(const Entity& e) : Entity(e) { OnLoad(); }
		virtual ~ScriptableEntity() { }

		virtual void OnLoad() { };
		virtual void OnStart() { };
		virtual void OnUpdate(Time t) { };
		virtual void onExit() { };

		virtual bool OnKeyPressed(const KeyPressedEvent& e) { return false; }
		virtual bool OnKeyReleased(const KeyReleasedEvent& e) { return false; }
		virtual bool OnMouseMoved(const MouseMovedEvent& e) { return false; }
		virtual bool OnMouseScrolled(const MouseScrolledEvent& e) { return false; }
		virtual bool OnMouseButtonPressed(const MouseButtonPressedEvent& e) { return false; }
		virtual bool OnMouseButtonReleased(const MouseButtonReleasedEvent& e) { return false; }
		virtual bool OnWindowResized(const WindowResizedEvent& e) { return false; }

		void SetUpdating(bool value) { mUpdating = value; }
		bool IsUpdating() const { return mUpdating; }

	private:
		bool mUpdating = true;
	};
}