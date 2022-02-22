#pragma once

#define OE_EVENT_DEFINITION(type, categories, repr) \
	static EventType GetType() { return EventType::type; } \
	static unsigned int GetCategoryFlags() { return EventCategory::categories; } \
	virtual EventType getType() const override { return EventType::type; } \
	virtual unsigned int getCategoryFlags() const override { return EventCategory::categories; } \
	virtual std::string toString() const override \
	{ \
		return "<" + std::string(#type) + ": " + repr + ">"; \
	}

namespace OrbitalEngine
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

		virtual EventType getType() const = 0;
		virtual unsigned int getCategoryFlags() const = 0;
		virtual std::string toString() const = 0;

		void setHandled(bool value) { m_handled = value; }

	private:
		friend std::ostream& operator<<(std::ostream& os, const Event& e);

		bool m_handled = false;
	};

	class EventDispatcher
	{
	public:
		EventDispatcher(Event& e) : m_event(e) { }

		template <typename T>
		bool dispatch(std::function<bool(T&)> func)
		{
			if (m_event.getType() == T::GetType())
			{
				m_event.setHandled(func(*(T*)&m_event));
				return true;
			}
			return false;
		}

	private:
		Event& m_event;
	};
}
