#pragma once

#include "OrbitalEngine/Utils.h"
#include "OrbitalEngine/Graphics/Window.h"
#include "OrbitalEngine/Components/NativeScript.h"
#include "OrbitalEngine/Logic/Scene.h"

namespace Orbital
{
	class Camera;
	class Scene;

	class Application
	{
	public:
		Application();
		virtual ~Application();
		
		void OnEvent(Event& e);
		virtual bool OnKeyPressed(KeyPressedEvent& e) { return false; }
		virtual bool OnKeyReleased(KeyReleasedEvent& e) { return false; }
		virtual bool OnMouseMoved(MouseMovedEvent& e) { return false; }
		virtual bool OnMouseScrolled(MouseScrolledEvent& e) { return false; }
		virtual bool OnMouseButtonPressed(MouseButtonPressedEvent& e) { return false; }
		virtual bool OnMouseButtonReleased(MouseButtonReleasedEvent& e) { return false; }
		virtual bool OnWindowResized(WindowResizedEvent& e) { return false; }

		virtual void OnLoad() = 0;
		virtual void OnStart() = 0;
		virtual void OnUpdate(Time dt) = 0;

		void Run();

	protected:
		Scope<Window> mWindow;
		Scene mScene;
		Scene* mActiveScene;

		Time mAverageTimePerFrame;
		Time mTimeAtLastUpdate;
	};
}