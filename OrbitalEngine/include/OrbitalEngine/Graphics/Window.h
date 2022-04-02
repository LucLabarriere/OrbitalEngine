#pragma once

#include "OrbitalEngine/Utils.h"
#include "OrbitalEngine/Events.h"

namespace Orbital
{
	class Window
	{
	public:
		Window(unsigned int width, unsigned int height, const std::string& title)
			: m_width(width), m_height(height), m_title(title) { }
		virtual ~Window() {};

		virtual bool shouldClose() = 0;
		virtual void onUpdate() = 0;
		virtual void shutdown() = 0;

		unsigned int getWidth() { return m_width; }
		unsigned int getHeight() { return m_height; }
		virtual void* getNativeWindow() const = 0;

		void applicationCallback(Event& e) { m_eventCallback(e); }
		void setApplicationCallBack(std::function<void(Event& e)> callback) { m_eventCallback = callback; };

		static Window* Create(unsigned int width, unsigned int height, const std::string& title);

	protected:
		bool m_initialized = false;
		unsigned int m_width;
		unsigned int m_height;
		std::string m_title;
		std::function<void(Event& e)> m_eventCallback;
	};
}