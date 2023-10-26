#pragma once

#include <et/core.hpp>
#include <et/singleton.hpp>
#include <queue>
#include "event.hpp"

namespace EngineThingy {
	class ET_API EventSystem : public Singleton<std::unique_ptr<EventSystem>> {
	private:
		EventSystem();
		std::array<std::vector<EventDispatcher>,
				   static_cast<size_t>(EventType::NEventTypes)>
			_listeners;
		std::queue<EventReference> _pendingEvents;

	public:
		void Update(Timing delta);
		static EventSystem &Init();
		template <class E, class F>
		void AddListener(F &&callback) {
			static_assert(is_event_v<E>, "Invalid event type");
			_listeners[static_cast<size_t>(E::type)].emplace_back(
				EventDispatcher::Create<E>(std::forward<F>(callback)));
		}
		void EnqueueEvent(EventReference e);
		~EventSystem();
	};

} // namespace EngineThingy
