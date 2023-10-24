#pragma once

#include "core.hpp"

namespace EngineThingy {

	template <class Ptr>
	class Singleton {
	protected:
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
