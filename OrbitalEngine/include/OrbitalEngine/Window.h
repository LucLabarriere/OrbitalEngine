#pragma once

#include "OrbitalEngine/Context.h"
#include "OrbitalEngine/Tools.h"

namespace OrbitalEngine
{
	class ORBITAL_API Window
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

		static Window* Create(unsigned int width, unsigned int height, const std::string& title);

	protected:
		bool m_initialized = false;
		unsigned int m_width;
		unsigned int m_height;
		std::string m_title;
	};
}