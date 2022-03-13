#pragma once

#include "OrbitalEngine/Events/MainEvents.h"

namespace OrbitalEngine
{
	class WindowResizedEvent : public Event
	{
	public:
		WindowResizedEvent(unsigned int width, unsigned int height)
			: Event(), m_width(width), m_height(height) { }

		unsigned int getWidth() const { return m_width; }
		unsigned int getHeight() const { return m_height; }

		OE_EVENT_DEFINITION(
			WindowResized,
			WindowEventCategory,
			fmt::format("{}, {}", m_width, m_height)
		)

	private:
		unsigned int m_width;
		unsigned int m_height;
	};
}
