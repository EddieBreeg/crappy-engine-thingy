#pragma once

#include "core.hpp"
#include "singleton.hpp"

namespace EngineThingy {

	class ET_API RNG : public Singleton<RNG *> {
	private:
		RNG();
		uint64_t _state[4];

	public:
		using result_type = uint64_t;
		static RNG &Init();
		void Seed(result_type s);
		result_type operator()();
		static constexpr result_type min() { return 0; }
		static constexpr result_type max() {
			return static_cast<result_type>(-1);
		}
		~RNG() = default;
	};

} // namespace EngineThingy
