#include <et/events/window.hpp>

namespace EngineThingy {
	WindowResizeEvent::WindowResizeEvent(
		WindowResizeEvent::WindowSize old,
		WindowResizeEvent::WindowSize newSize) :
		oldSize(old), newSize(newSize) {}

	WindowResizeEvent::operator std::string() const {
		std::stringstream ss;
		ss << '(' << oldSize.first << ", " << oldSize.second << ") -> ("
		   << newSize.first << ", " << newSize.second << ')';
		return ss.str();
	}
} // namespace EngineThingy
