#pragma once

#include <et/core.hpp>
#include <et/singleton.hpp>
#include <et/logsystem.hpp>
#include <queue>
#include "event.hpp"

namespace EngineThingy {
	class ET_API EventSystem : public Singleton<std::unique_ptr<EventSystem>> {
	private:
		EventSystem();
		std::array<std::list<EventDispatcher>,
				   static_cast<size_t>(EventType::NEventTypes)>
			_listeners;
		// std::pmr::monotonic_buffer_resource _mbr;
		std::queue<EventReference> _pendingEvents;

	public:
		void Update(Timing delta);
		static EventSystem &Init();
		template <class E, class F>
		void AddListener(F &&callback, LayerMask targetLayers = LAYERS_ALL) {
			static_assert(is_event_v<E>, "Invalid event type");
			auto &list = _listeners[static_cast<size_t>(E::type)];
			auto disp  = EventDispatcher::Create<E>(std::forward<F>(callback),
													targetLayers);
			auto it	   = list.begin();
			while (it != list.end()) {
				if (it->GetTargetLayers() < targetLayers) {
					list.insert(it, std::move(disp));
					break;
				}
			}
			if (it == list.end()) list.emplace_back(std::move(disp));
		}
		void EnqueueEvent(EventReference e);
		~EventSystem();
	};

} // namespace EngineThingy
