#pragma once

#include "OrbitalEngine/Events/MainEvents.h"

namespace OrbitalEngine
{
	class MouseEvent : public Event
	{
	public:
		MouseEvent(float x, float y)
			: Event(), m_xPos(x), m_yPos(y) { }

		float getX() const { return m_xPos; }
		float getY() const { return m_yPos; }

	protected:
		float m_xPos;
		float m_yPos;
	};

	class MouseMovedEvent : public MouseEvent
	{
	public:
		MouseMovedEvent(float x, float y)
			: MouseEvent(x, y) { }

		OE_EVENT_DEFINITION(
			MouseMoved,
			InputEventCategory | MouseEventCategory,
			fmt::format("{}, {}", m_xPos, m_yPos)
		)
	};

	class MouseButtonEvent : public MouseEvent
	{
	public:
		MouseButtonEvent(float x, float y, unsigned int button)
			: MouseEvent(x, y), m_button(button) { }

		unsigned int getButton() const { return m_button; }

	protected:
		unsigned int m_button;
	};

	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(float x, float y, unsigned int button)
			: MouseButtonEvent(x, y, button) { }

		OE_EVENT_DEFINITION(
			MouseButtonPressed,
			InputEventCategory | MouseEventCategory,
			fmt::format("{}, {}, {}", m_xPos, m_yPos, m_button)
		)
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(float x, float y, unsigned int button)
			: MouseButtonEvent(x, y, button) { }

		OE_EVENT_DEFINITION(
			MouseButtonReleased,
			InputEventCategory | MouseEventCategory,
			fmt::format("{}, {}, {}", m_xPos, m_yPos, m_button)
		)
	};

	class MouseScrolledEvent : public MouseEvent
	{
	public:
		MouseScrolledEvent(float x, float y, float xOffset, float yOffset)
			: MouseEvent(x, y), m_xOffset(xOffset), m_yOffset(yOffset) { }

		float getXOffset() const { return m_xOffset; }
		float getYOffset() const { return m_yOffset; }

		OE_EVENT_DEFINITION(
			MouseScrolled,
			InputEventCategory | MouseEventCategory,
			fmt::format("{}, {}, {}, {}", m_xPos, m_yPos, m_xOffset, m_yOffset)
		)

	private:
		float m_xOffset;
		float m_yOffset;
	};
}