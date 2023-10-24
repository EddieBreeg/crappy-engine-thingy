#pragma once

#include "core.hpp"
#include "meta.hpp"

namespace EngineThingy {

	template <class Ptr>
	class Singleton {
	protected:
		static_assert(is_dereferenceable_v<Ptr> &&
						  std::is_reference_v<libstra::dereference_t<Ptr>>,
					  "Ptr is not a pointer type");
		static Ptr _instance;
		Singleton() = default;

	public:
		static auto &Instance() {
			assert(_instance);
			return *_instance;
		}

		Singleton(Singleton &) = delete;
		Singleton &operator=(Singleton &) = delete;
	};

	template <class Ptr>
	Ptr Singleton<Ptr>::_instance = nullptr;
} // namespace EngineThingy
