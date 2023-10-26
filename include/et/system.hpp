#pragma once

#include "meta.hpp"

namespace EngineThingy {

	namespace _impl {
		template <class T, class = void>
		struct is_system_type : std::false_type {};

		template <class T>
		struct is_system_type<
			T,
			std::void_t<std::enable_if_t<is_singleton_v<T>>,
						decltype(T::Instance().Update(std::declval<Timing>()))>>
			: std::true_type {};
	} // namespace _impl

	template <class T>
	static constexpr bool is_system_type_v = _impl::is_system_type<T>::value;

	class ET_API SystemInstance {
	private:
		void (*_updateFunc)(Timing) = nullptr;
		SystemInstance(void (*f)(Timing)) : _updateFunc(f) {}

	public:
		template <class S>
		static SystemInstance Create() {
			static_assert(is_system_type_v<S>, "S is not a valid system class");
			return SystemInstance([](Timing d) { S::Instance().Update(d); });
		}
		void Update(Timing delta) const { _updateFunc(delta); }
		SystemInstance(SystemInstance &) = delete;
		SystemInstance(SystemInstance &&other) :
			_updateFunc(other._updateFunc) {
			other._updateFunc = nullptr;
		}
		SystemInstance &operator=(SystemInstance &) = delete;
		~SystemInstance() = default;
	};

} // namespace EngineThingy
