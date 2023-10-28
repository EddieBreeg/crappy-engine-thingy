#include <et/events/event.hpp>

namespace EngineThingy {
	EventDispatcher::EventDispatcher(EventDispatcher::Callback cbk,
									 EventDispatcher::TypeFuncPtr ptr,
									 LayerMask l) :
		_callback(std::move(cbk)), _getType(ptr), _targetLayers(l) {}

	void EventDispatcher::operator()(const Event &evt) {
		ET_ASSERT(evt.GetType() == _getType());
		_callback(evt);
	}
} // namespace EngineThingy
