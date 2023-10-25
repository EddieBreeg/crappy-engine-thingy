#pragma once

#include "event.hpp"

namespace EngineThingy {
	class ApplicationStartEvent : public Event {
	public:
		ApplicationStartEvent() = default;
		ET_EVENT_CLASS(EventType::ApplicationStart, EventCategory::Application);
	};
	class ApplicationQuitEvent : public Event {
	public:
		ApplicationQuitEvent() = default;
		ET_EVENT_CLASS(EventType::ApplicationQuit, EventCategory::Application);
	};

} // namespace EngineThingy
