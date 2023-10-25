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

		template <class F, class E, class Tuple, size_t... I>
		static void apply(F &&f, const E &evt, Tuple &&args,
						  std::index_sequence<I...>) {
			f(evt, std::get<I>(args)...);
		}
		template <class F, class E, class Tuple>
		static void apply(F &&f, const E &evt, Tuple &&args) {
			using ISeq = std::make_index_sequence<
				std::tuple_size_v<std::decay_t<Tuple>>>;
			apply(std::forward<F>(f), evt, std::forward<Tuple>(args), ISeq{});
		}

	public:
		template <class Evt, class F, class... Args>
		static EventDispatcher Create(F &&func, Args &&...args) {
			static_assert(is_event_v<Evt>, "Invalid event type");
			using RawFunc_t = std::decay_t<F>;
			static_assert(
				libstra::is_invocable_v<RawFunc_t, const Evt &, Args...>,
				"Invalid callback");
			static_assert(
				std::is_void_v<decltype(func(std::declval<Evt>(),
											 std::forward<Args>(args)...))>,
				"Callback must not return a value");
			using ArgTuple = std::tuple<std::decay_t<Args>...>;
			return EventDispatcher(
				[f = std::forward<RawFunc_t>(func),
				 a = ArgTuple{ libstra::forward<Args>(args)... }](
					const Event &evt) {
					EventDispatcher::apply(f, dynamic_cast<const Evt &>(evt),
										   a);
				},
				[]() { return Evt::type; });
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
