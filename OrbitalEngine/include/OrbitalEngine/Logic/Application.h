#pragma once

#include "OrbitalEngine/Utils.h"
#include "OrbitalEngine/Graphics/Window.h"
#include "OrbitalEngine/Logic/LayerStack.h"
#include "OrbitalEngine/Graphics/CameraController.h"

namespace OrbitalEngine
{
	class Camera;

	class Application
	{
	public:
		Application();
		virtual ~Application();
		
		void onEvent(Event& e);
		virtual bool onKeyPressed(KeyPressedEvent& e) { return false; }
		virtual bool onKeyReleased(KeyReleasedEvent& e) { return false; }
		virtual bool onMouseMoved(MouseMovedEvent& e) { return false; }
		virtual bool onMouseScrolled(MouseScrolledEvent& e) { return false; }
		virtual bool onMouseButtonPressed(MouseButtonPressedEvent& e) { return false; }
		virtual bool onMouseButtonReleased(MouseButtonReleasedEvent& e) { return false; }
		virtual bool onWindowResized(WindowResizedEvent& e) { return false; }

		virtual void onStart() = 0;
		virtual void onUpdate(Time dt) = 0;
		void run();
		

	protected:
		Scope<Window> m_window;
		Scope<LayerStack> m_layerStack;

		Time m_averageTimePerFrame;
		Time m_timeAtLastUpdate;
	};
}