#include <et/events/event_system.hpp>

namespace EngineThingy {

	EventSystem &EventSystem::Init() {
		ET_ENSURE(!_instance);
		static EventSystem sys;
		return *(_instance = &sys);
	}
	void EventSystem::Update(Timing delta) {}
	EventSystem::EventSystem() {}
	EventSystem::~EventSystem() {}

} // namespace EngineThingy
