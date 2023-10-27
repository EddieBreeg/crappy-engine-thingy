#pragma once

#include "event_system.hpp"

namespace EngineThingy {
	enum MouseButton {
		Mouse1,
		Mouse2,
		Mouse3,
		Mouse4,
		Mouse5,
		Mouse6,
		Mouse7,
		Mouse8,
	};

	class ET_API MouseButtonPressedEvent : public Event {
	public:
		MouseButton code;
		MouseButtonPressedEvent(MouseButton b) : code(b) {}
		ET_EVENT_CLASS(EventType::MouseButtonPress,
					   ET_EVENT_CATEGORY_MASK(EventCategory::Input,
											  EventCategory::Mouse))
	};
	class ET_API MouseButtonReleasedEvent : public Event {
	public:
		MouseButton code;
		MouseButtonReleasedEvent(MouseButton b) : code(b) {}
		ET_EVENT_CLASS(EventType::MouseButtonRelease,
					   ET_EVENT_CATEGORY_MASK(EventCategory::Input,
											  EventCategory::Mouse))
	};

} // namespace EngineThingy
