#pragma once

#include "OrbitalEngine/Utils.h"
#include "OrbitalEngine/Events.h"

namespace OrbitalEngine
{
	class LayerStack;

	class Layer
	{
	public:
		enum State
		{
			Running,
			Paused,
			Stopped
		};

	public:
		Layer(const std::string& tag);
		virtual ~Layer() { }

		void play();
		void pause();
		void stop();

		virtual void update(Time dt) = 0;

		virtual bool onKeyPressed(KeyPressedEvent& e) { return false; }
		virtual bool onKeyReleased(KeyReleasedEvent& e) { return false; }
		virtual bool onMouseMoved(MouseMovedEvent& e) { return false; }
		virtual bool onMouseScrolled(MouseScrolledEvent& e) { return false; }
		virtual bool onMouseButtonPressed(MouseButtonPressedEvent& e) { return false; }
		virtual bool onMouseButtonReleased(MouseButtonReleasedEvent& e) { return false; }
		virtual bool onWindowResized(WindowResizedEvent& e) { return false; }

	private:
		void setLayerId(int layerId) { m_layerId = layerId;  }

	private:
		friend LayerStack;

		State m_state = State::Running;
		std::string m_tag;
		int m_layerId = -1;
	};
}
