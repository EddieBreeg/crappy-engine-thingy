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
		MouseButtonPressedEvent(MouseButton b, LayerMask m = LAYERS_ALL) :
			Event(m), code(b) {}
		ET_EVENT_CLASS(EventType::MouseButtonPress,
					   ET_EVENT_CATEGORY_MASK(EventCategory::Input,
											  EventCategory::Mouse))
	};
	class ET_API MouseButtonReleasedEvent : public Event {
	public:
		MouseButton code;
		MouseButtonReleasedEvent(MouseButton b, LayerMask m = LAYERS_ALL) :
			Event(m), code(b) {}
		ET_EVENT_CLASS(EventType::MouseButtonRelease,
					   ET_EVENT_CATEGORY_MASK(EventCategory::Input,
											  EventCategory::Mouse))
	};

	class ET_API CursorMoveEvent : public Event {
	public:
		std::pair<double, double> oldPos, newPos;
		CursorMoveEvent(std::pair<double, double> oldP,
						std::pair<double, double> newP,
						LayerMask m = LAYERS_ALL) :
			Event(m), oldPos(oldP), newPos(newP) {}
		ET_EVENT_CLASS(EventType::MouseMove,
					   ET_EVENT_CATEGORY_MASK(EventCategory::Input,
											  EventCategory::Mouse))
		operator std::string() const override {
			return fmt::format("Mouse Move ({}, {}) -> ({}, {})", oldPos.first,
							   oldPos.second, newPos.first, newPos.second);
		}
	};

} // namespace EngineThingy
