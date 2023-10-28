#pragma once

#include <et/core.hpp>

namespace EngineThingy {
	enum class EventType : int {
		None = 0,

		WindowClose,
		WindowResize,
		WindowMove,
		WindowFocus,

		MouseMove,
		MouseButtonPress,
		MouseButtonRelease,

		KeyPress,
		KeyRelease,

		ApplicationStart,
		ApplicationQuit,

		NEventTypes
	};
	enum class EventCategory : int {
		None = 0,
		Application = BIT(0),
		Window = BIT(1),
		Input = BIT(2),
		Mouse = BIT(3),
		Keyboard = BIT(4),
	};

	constexpr bool checkCategory(EventCategory mask, EventCategory cat) {
		return static_cast<int>(mask) & static_cast<int>(cat);
	}

#define ET_EVENT_CATEGORY_MASK(...)                                            \
	EngineThingy::BinaryOr<EventCategory>(__VA_ARGS__)

	namespace _impl {
		template <class T, class = void>
		struct is_event : std::false_type {};

		template <class T>
		struct is_event<
			T,
			std::enable_if_t<
				std::is_same_v<const EventType, decltype(T::type)> &&
				std::is_same_v<const EventCategory, decltype(T::categories)> &&
				std::is_same_v<const char *,
							   decltype(std::declval<T>().GetName())>>>
			: std::true_type {};
	} // namespace _impl

	template <class T>
	static constexpr bool is_event_v = _impl::is_event<T>::value;

	class ET_API Event {
	public:
		Event() = default;
		[[nodiscard]]
		virtual EventType GetType() const noexcept = 0;
		[[nodiscard]]
		virtual EventCategory GetCategories() const noexcept = 0;
		[[nodiscard]]
		virtual const char *GetName() const noexcept = 0;

		virtual operator std::string() const { return GetName(); }
		[[nodiscard]]
		bool HasCategory(EventCategory cat) const noexcept {
			return ENUM_TO_INT(cat) | ENUM_TO_INT(GetCategories());
		}

		virtual ~Event() = default;
	};

#define ET_EVENT_CLASS(Type, Categories)                                       \
	static constexpr EngineThingy::EventType type = Type;                      \
	static constexpr EngineThingy::EventCategory categories = Categories;      \
	[[nodiscard]]                                                              \
	virtual EngineThingy::EventType GetType() const noexcept override {        \
		return type;                                                           \
	}                                                                          \
	[[nodiscard]]                                                              \
	virtual EngineThingy::EventCategory GetCategories()                        \
		const noexcept override {                                              \
		return categories;                                                     \
	}                                                                          \
	[[nodiscard]]                                                              \
	virtual const char *GetName() const noexcept override {                    \
		return #Type;                                                          \
	}

	class ET_API EventDispatcher {
		using TypeFuncPtr = EventType (*)();
		using Callback = libstra::unique_function<void(const Event &)>;

	public:
		template <class Evt, class F>
		static EventDispatcher Create(F &&func) {
			Callback cbk = [f = std::forward<F>(func)](const Event &e) {
				f((const Evt &)(e));
			};
			return EventDispatcher(std::move(cbk), []() { return Evt::type; });
		}
		void operator()(const Event &evt);
		EventType GetEventType() const noexcept { return _getType(); }
		EventDispatcher(EventDispatcher &&) = default;
		~EventDispatcher() = default;

	private:
		EventDispatcher(Callback cbk, TypeFuncPtr gt);
		Callback _callback;
		TypeFuncPtr _getType = []() { return EventType::None; };
	};

	using EventReference = std::unique_ptr<Event>;

} // namespace EngineThingy
