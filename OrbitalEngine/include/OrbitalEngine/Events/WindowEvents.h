#pragma once

#include "OrbitalEngine/Events/MainEvents.h"

namespace Orbital
{
	class WindowResizedEvent : public Event
	{
	public:
		WindowResizedEvent(unsigned int width, unsigned int height)
			: Event(), mWidth(width), mHeight(height) { }

		unsigned int GetWidth() const { return mWidth; }
		unsigned int GetHeight() const { return mHeight; }

		OE_EVENT_DEFINITION(
			WindowResized,
			WindowEventCategory,
			fmt::format("{}, {}", mWidth, mHeight)
		)

	private:
		unsigned int mWidth;
		unsigned int mHeight;
	};
}
