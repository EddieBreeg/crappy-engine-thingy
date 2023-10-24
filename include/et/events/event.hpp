#pragma once

#include <et/core.hpp>

namespace EngineThingy {
	enum class EventType : int {
		None = 0,

		WindowClose,
		WindowResize,
		WindowMove,

		MouseMove,
		MouseButtonPress,
		MouseButtonRelease,

		KeyPress,
		KeyRelease,

		ApplicationQuit,
	};
	enum class EventCategory : int {
		None = 0,
		Application = BIT(0),
		Window = BIT(1),
		Mouse = BIT(2),
		Keyboard = BIT(3),
	};

	template <EventCategory C>
	constexpr EventCategory buildEventCategoryMask() {
		return C;
	}
	template <EventCategory F, EventCategory S, EventCategory... N>
	constexpr EventCategory buildEventCategoryMask() {
		return static_cast<EventCategory>(
			static_cast<int>(F) |
			static_cast<int>(buildEventCategoryMask<S, N...>()));
	}
	constexpr bool checkCategory(EventCategory mask, EventCategory cat) {
		return static_cast<int>(mask) & static_cast<int>(cat);
	}

#define ET_EVENT_CATEGORY_MASK(...)                                            \
	EngineThingy::buildEventCategoryMask<__VA_ARGS__>()

#define ET_EVENT_CLASS_TYPE(T)                                                 \
	virtual EngineThingy::EventType Type() const override {                    \
		return T;                                                              \
	}                                                                          \
	virtual const char *Name() const override {                                \
		return #T;                                                             \
	}

	class ET_API Event {
	public:
		virtual EventType Type() const = 0;
		virtual const char *Name() const = 0;
		virtual EventCategory CategoryMask() const {
			return EventCategory::None;
		}
		inline bool HasCategory(EventCategory cat) const {
			return (int)CategoryMask() & (int)cat;
		}

	private:
	};

} // namespace EngineThingy
