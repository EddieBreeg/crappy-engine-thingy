#include <et/events/event.hpp>

namespace EngineThingy {
	EventDispatcher::EventDispatcher(EventDispatcher::Callback cbk,
									 EventDispatcher::TypeFuncPtr ptr,
									 LayerMask l) :
		_callback(std::move(cbk)), _getType(ptr), _targetLayers(l) {}

	bool EventDispatcher::operator()(const Event &evt) {
		ET_ASSERT(evt.GetType() == _getType());
		return _callback(evt);
	}
} // namespace EngineThingy
