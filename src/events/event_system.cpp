#include <et/events/event_system.hpp>
#include <et/logsystem.hpp>

namespace EngineThingy {

	EventSystem &EventSystem::Init() {
		ET_ASSERT(!_instance);
		auto *sys = new EventSystem();
		return *(_instance = std::unique_ptr<EventSystem>(sys));
	}
	void EventSystem::EnqueueEvent(EventReference e) {
		_pendingEvents.emplace(std::move(e));
	}
	void EventSystem::Update(Timing delta) {
		while (!_pendingEvents.empty()) {
			EventReference e = std::move(_pendingEvents.front());
			_pendingEvents.pop();

			size_t i = static_cast<size_t>(e->GetType());
			for (EventDispatcher &disp : _listeners[i]) {
				disp(*e);
			}
		}
	}
	EventSystem::EventSystem() {}
	EventSystem::~EventSystem() {}

} // namespace EngineThingy
