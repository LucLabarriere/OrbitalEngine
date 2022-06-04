#pragma once

#include "OrbitalEngine/Events/MainEvents.h"

namespace Orbital
{
	class MouseEvent : public Event
	{
	public:
		MouseEvent(float x, float y)
			: Event(), mXPos(x), mYPos(y) { }

		float GetX() const { return mXPos; }
		float GetY() const { return mYPos; }

	protected:
		float mXPos;
		float mYPos;
	};

	class MouseMovedEvent : public MouseEvent
	{
	public:
		MouseMovedEvent(float x, float y)
			: MouseEvent(x, y) { }

		OE_EVENT_DEFINITION(
			MouseMoved,
			InputEventCategory | MouseEventCategory,
			fmt::format("{}, {}", mXPos, mYPos)
		)
	};

	class MouseButtonEvent : public MouseEvent
	{
	public:
		MouseButtonEvent(float x, float y, unsigned int button)
			: MouseEvent(x, y), mButton(button) { }

		unsigned int GetButton() const { return mButton; }

	protected:
		unsigned int mButton;
	};

	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(float x, float y, unsigned int button)
			: MouseButtonEvent(x, y, button) { }

		OE_EVENT_DEFINITION(
			MouseButtonPressed,
			InputEventCategory | MouseEventCategory,
			fmt::format("{}, {}, {}", mXPos, mYPos, mButton)
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
			fmt::format("{}, {}, {}", mXPos, mYPos, mButton)
		)
	};

	class MouseScrolledEvent : public MouseEvent
	{
	public:
		MouseScrolledEvent(float x, float y, float xOffset, float yOffset)
			: MouseEvent(x, y), mXOffset(xOffset), mYOffset(yOffset) { }

		float GetXOffset() const { return mXOffset; }
		float GetYOffset() const { return mYOffset; }

		OE_EVENT_DEFINITION(
			MouseScrolled,
			InputEventCategory | MouseEventCategory,
			fmt::format("{}, {}, {}, {}", mXPos, mYPos, mXOffset, mYOffset)
		)

	private:
		float mXOffset;
		float mYOffset;
	};
}