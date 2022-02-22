#pragma once

#include "OrbitalEngine/Events/Events.h"

namespace OrbitalEngine
{
	class KeyPressedEvent : public Event
	{
	public:
		KeyPressedEvent(int keyCode) : Event(), m_keyCode(keyCode) { }

		unsigned int getKeyCode() const { return m_keyCode; }

		OE_EVENT_DEFINITION(
			KeyPressed,
			InputEventCategory | KeyEventCategory,
			fmt::format("{}", m_keyCode)
		)

	private:
		int m_keyCode;
	};

	class KeyReleasedEvent : public Event
	{
	public:
		KeyReleasedEvent(int keyCode) : Event(), m_keyCode(keyCode) {}

		unsigned int getKeyCode() const { return m_keyCode; }

		OE_EVENT_DEFINITION(
			KeyReleased,
			InputEventCategory | KeyEventCategory,
			fmt::format("{}", m_keyCode)
		)

	private:
		int m_keyCode;
	};
}