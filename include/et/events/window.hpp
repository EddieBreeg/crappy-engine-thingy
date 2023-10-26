#pragma once

#include "event_system.hpp"

namespace EngineThingy {

	class ET_API WindowCloseEvent : public Event {
	public:
		WindowCloseEvent() = default;
		ET_EVENT_CLASS(EventType::WindowClose,
					   ET_EVENT_CATEGORY_MASK(EventCategory::Application,
											  EventCategory::Window))
	};

	class ET_API WindowResizeEvent : public Event {
	public:
		using WindowSize = std::pair<uint32_t, uint32_t>;
		WindowSize oldSize, newSize;
		WindowResizeEvent(WindowSize oldSize, WindowSize newSize);
		ET_EVENT_CLASS(EventType::WindowResize, EventCategory::Window);
		operator std::string() const override;
	};

	class ET_API WindowFocusEvent : public Event {
	public:
		bool focused;

		WindowFocusEvent(bool focused);
		operator std::string() const override;
		ET_EVENT_CLASS(EventType::WindowFocus, EventCategory::Window);
	};

	class ET_API WindowMoveEvent : public Event {
	public:
		int x, y;

		WindowMoveEvent(int x, int y);
		operator std::string() const override;
		ET_EVENT_CLASS(EventType::WindowMove, EventCategory::Window);
	};

} // namespace EngineThingy
