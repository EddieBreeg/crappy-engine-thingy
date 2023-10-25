#pragma once

#include "event.hpp"

namespace EngineThingy {

	class KeyPressedEvent : public Event {
	private:
		int _code;
		bool _repeat;

	public:
		KeyPressedEvent(int code, bool repeat = false) noexcept :
			_code(code), _repeat(repeat) {}
		[[nodiscard]]
		bool IsRepeat() const noexcept {
			return _repeat;
		}
		[[nodiscard]]
		int GetCode() const noexcept {
			return _code;
		}

		ET_EVENT_CLASS(EventType::KeyPress,
					   ET_EVENT_CATEGORY_MASK(EventCategory::Input,
											  EventCategory::Keyboard))
	};
	class KeyReleasedEvent : public Event {
	private:
		int _code;

	public:
		KeyReleasedEvent(int code) noexcept : _code(code) {}
		[[nodiscard]]
		int GetCode() const noexcept {
			return _code;
		}

		ET_EVENT_CLASS(EventType::KeyPress,
					   ET_EVENT_CATEGORY_MASK(EventCategory::Input,
											  EventCategory::Keyboard))
	};

} // namespace EngineThingy
