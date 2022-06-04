#pragma once

#include "OrbitalEngine/Events/MainEvents.h"

namespace Orbital
{
	class KeyPressedEvent : public Event
	{
	public:
		KeyPressedEvent(int keyCode) : Event(), mKeyCode(keyCode) { }

		unsigned int GetKeyCode() const { return mKeyCode; }

		OE_EVENT_DEFINITION(
			KeyPressed,
			InputEventCategory | KeyEventCategory,
			fmt::format("{}", mKeyCode)
		)

	private:
		int mKeyCode;
	};

	class KeyReleasedEvent : public Event
	{
	public:
		KeyReleasedEvent(int keyCode) : Event(), mKeyCode(keyCode) {}

		unsigned int GetKeyCode() const { return mKeyCode; }

		OE_EVENT_DEFINITION(
			KeyReleased,
			InputEventCategory | KeyEventCategory,
			fmt::format("{}", mKeyCode)
		)

	private:
		int mKeyCode;
	};
}