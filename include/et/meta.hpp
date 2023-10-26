#pragma once

#include "pch.h"
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
					!std::is_copy_constructible_v<T> &&
					!std::is_copy_assignable_v<T> &&
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

	namespace _impl {
		template <class F>
		struct function_info;

		template <class R, class... Args>
		struct function_info<R(Args...)> {
			using ArgPack = Pack_t<Args...>;
			using ResType = R;
		};
		template <class R, class... Args>
		struct function_info<R(Args...) const> {
			using ArgPack = Pack_t<Args...>;
			using ResType = R;
		};
		template <class R, class... Args>
		struct function_info<R(Args...) noexcept> {
			using ArgPack = Pack_t<Args...>;
			using ResType = R;
		};
		template <class R, class... Args>
		struct function_info<R(Args...) const noexcept> {
			using ArgPack = Pack_t<Args...>;
			using ResType = R;
		};

		template <class Func, class C>
		struct function_info<Func C::*> : function_info<Func> {
			using Class = C;
		};

		template <class F, class C, class... Args>
		static auto bindImpl(F(C::*mp), C *instance, Pack_t<Args...> = {}) {
			return [mp, instance](Args &&...args) {
				using R = typename function_info<F>::ResType;
				if constexpr (std::is_void_v<R>)
					(instance->*mp)(std::forward<Args>(args)...);
				else return (instance->*mp)(std::forward<Args>(args)...);
			};
		}
		// template <size_t N, class Pack>
		// struct remove_n_args;

		// template <size_t N, class F, class... O>
		// struct remove_n_args<N, Pack_t<F, O...>> {
		// 	using type = std::conditional_t<
		// 		N == 0, Pack_t<F, O...>,
		// 		typename remove_n_args<N - 1, Pack_t<O...>>::type>;
		// };
		// template <size_t N>
		// struct remove_n_args<N, Pack_t<>> {
		// 	using type = Pack_t<>;
		// };
		// template <size_t N, class... Args>
		// using remove_n_args_t =
		// 	typename remove_n_args<N, Pack_t<Args...>>::type;

	} // namespace _impl

	template <class MP, class C>
	static auto BindMethod(MP C::*mp, C *instance) {
		static_assert(std::is_member_function_pointer_v<decltype(mp)>,
					  "Invalid member function pointer");
		using Pack_t = typename _impl::function_info<MP>::ArgPack;
		return _impl::bindImpl(mp, instance, Pack_t{});
	}
	template <class F, class... Args>
	static auto Bind(F &&f, Args &&...args) {
		static_assert(std::is_invocable_v<F, Args...>,
					  "Invalid function object");
		using Tuple = std::tuple<std::decay_t<Args>...>;
		using Func = std::decay_t<F>;
		return [f = Func{ std::forward<F>(f) },
				a = Tuple{ std::forward<Args>(args)... }]() {
			return std::apply(f, a);
		};
	}

} // namespace EngineThingy
