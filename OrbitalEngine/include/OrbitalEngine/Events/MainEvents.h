#pragma once

#include <fmt/core.h>

#define OE_EVENT_DEFINITION(type, categories, repr) \
	static EventType GetStaticType() { return EventType::type; } \
	static unsigned int GetStaticCategoryFlags() { return EventCategory::categories; } \
	virtual EventType GetType() const override { return EventType::type; } \
	virtual unsigned int GetCategoryFlags() const override { return EventCategory::categories; } \
	virtual std::string ToString() const override \
	{ \
		return "<" + std::string(#type) + ": " + repr + ">"; \
	}

namespace Orbital
{
	enum EventCategory
	{
		ApplicationEventCategory =	OE_BIT(0),
		WindowEventCategory =		OE_BIT(1),
		InputEventCategory =		OE_BIT(2),
		KeyEventCategory =			OE_BIT(3),
		MouseEventCategory =		OE_BIT(4),
		MouseButtonEventCategory =	OE_BIT(5)
	};

	enum EventType
	{
		WindowClosed,
		WindowResized,
		KeyPressed,
		KeyReleased,
		MouseMoved,
		MouseButtonPressed,
		MouseButtonReleased,
		MouseScrolled
	};

	class Event
	{
	public:
		Event() { };

		virtual EventType GetType() const = 0;
		virtual unsigned int GetCategoryFlags() const = 0;
		virtual std::string ToString() const = 0;

		void SetHandled(bool value) { mHandled = value; }

	private:
		friend std::ostream& operator<<(std::ostream& os, const Event& e);

		bool mHandled = false;
	};

	class EventDispatcher
	{
	public:
		EventDispatcher(Event& e) : mEvent(e) { }

		template <typename T>
		bool Dispatch(std::function<bool(T&)> func)
		{
			if (mEvent.GetType() == T::GetStaticType())
			{
				mEvent.SetHandled(func(*(T*)&mEvent));
				return true;
			}
			return false;
		}

	private:
		Event& mEvent;
	};
}
