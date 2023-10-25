#pragma once

#include <et/core.hpp>
#include <et/fast_hash.h>

namespace EngineThingy {

	namespace _impl {
		template <class T, class = void>
		struct Hash;

		template <class Int>
		struct IntHash {
			static_assert(std::is_integral_v<Int>, "Int is not an int type");
			uint64_t seed = 0;
			[[nodiscard]]
			constexpr size_t
			operator()(Int x) const noexcept {
				return x ^ seed;
			}
		};

		template <>
		struct Hash<int8_t> : public IntHash<int8_t> {};
		template <>
		struct Hash<uint8_t> : public IntHash<uint8_t> {};
		template <>
		struct Hash<int16_t> : public IntHash<int16_t> {};
		template <>
		struct Hash<uint16_t> : public IntHash<uint16_t> {};
		template <>
		struct Hash<int32_t> : public IntHash<int32_t> {};
		template <>
		struct Hash<uint32_t> : public IntHash<uint32_t> {};
		template <>
		struct Hash<int64_t> : public IntHash<int64_t> {};
		template <>
		struct Hash<uint64_t> : public IntHash<uint64_t> {};

		template <class T>
		struct Hash<T, std::enable_if_t<std::is_enum_v<T>>> {
			uint64_t seed = 0;
			constexpr size_t operator()(T x) const noexcept {
				using Int = std::underlying_type_t<T>;
				return static_cast<Int>(x) ^ seed;
			}
		};
		template <class T>
		struct Hash<T *> {
			uint64_t seed = 0;
			constexpr size_t operator()(T *x) const noexcept {
				return static_cast<std::intptr_t>(x) ^ seed;
			}
		};
		template <>
		struct Hash<std::string_view> {
			uint64_t seed = 0;
			size_t operator()(std::string_view x) const noexcept {
				return fasthash64(x.data(), x.length(), seed);
			}
		};
		template <>
		struct Hash<std::string> {
			uint64_t seed = 0;
			size_t operator()(const std::string &x) const noexcept {
				return fasthash64(x.data(), x.length(), seed);
			}
		};

	} // namespace _impl

	template <class T>
	struct Hash : _impl::Hash<T> {};

	template <class T>
	static constexpr size_t get_hash(T &&x, uint64_t seed = 0) {
		return Hash<std::decay_t<T>>{ seed }(x);
	}

} // namespace EngineThingy
