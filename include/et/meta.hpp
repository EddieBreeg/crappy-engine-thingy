#pragma once

#include "core.hpp"
#include <type_traits>
#include <libstra/utility.hpp>

namespace EngineThingy {

	template <class T>
	struct type_identity {
		using type = T;
	};

	template <class T>
	struct remove_cv : type_identity<T> {};
	template <class T>
	struct remove_cv<const T> : type_identity<T> {};
	template <class T>
	struct remove_cv<volatile T> : type_identity<T> {};
	template <class T>
	struct remove_cv<const volatile T> : type_identity<T> {};
	template <class T>
	struct remove_cv<const T &> : type_identity<T &> {};
	template <class T>
	struct remove_cv<volatile T &> : type_identity<T &> {};
	template <class T>
	struct remove_cv<const volatile T &> : type_identity<T &> {};
	template <class T>
	struct remove_cv<const T *> : type_identity<T *> {};
	template <class T>
	struct remove_cv<volatile T *> : type_identity<T *> {};
	template <class T>
	struct remove_cv<const volatile T *> : type_identity<T *> {};

	template <class T>
	using remove_cv_t = typename remove_cv<T>::type;

	namespace _impl {
		template <class... Args>
		struct Pack_t {};

		template <class T, class Args, class = void>
		struct is_singleton : std::false_type {};

		template <class T, class... Args>
		struct is_singleton<
			T, Pack_t<Args...>,
			std::void_t<
				decltype(T::Init(std::declval<Args>()...)),
				std::enable_if_t<
					!std::is_default_constructible_v<T> &&
					!std::is_constructible_v<T, Args...> &&
					std::is_same_v<T &, remove_cv_t<decltype(T::Instance())>>>>>
			: std::true_type {};
	} // namespace _impl

	template <class T, class... Args>
	static constexpr bool is_singleton_v =
		_impl::is_singleton<T, _impl::Pack_t<Args...>>::value;

	template <class F, class... Args>
	using invoke_t = decltype(std::declval<F>()(std::declval<Args>()...));

	namespace _impl {
		template <class T, class = void>
		struct is_dereferenceable : std::false_type {};

		template <class T>
		struct is_dereferenceable<T, std::void_t<libstra::dereference_t<T>>>
			: std::true_type {};

	} // namespace _impl

	template <class T>
	static constexpr bool is_dereferenceable_v =
		_impl::is_dereferenceable<T>::value;

} // namespace EngineThingy
