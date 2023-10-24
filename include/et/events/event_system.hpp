#pragma once

#include <et/core.hpp>
#include <et/singleton.hpp>

namespace EngineThingy {
	class ET_API EventSystem : public Singleton<EventSystem *> {
	private:
		EventSystem(/* args */);

	public:
		void Update(Timing delta);
		static EventSystem &Init();
		~EventSystem();
	};

} // namespace EngineThingy
