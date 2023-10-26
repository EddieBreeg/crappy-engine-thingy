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

} // namespace EngineThingy
