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
	WindowMoveEvent::operator std::string() const {
		std::stringstream ss;
		ss << '(' << x << ", " << y << ')';
		return ss.str();
	}
	WindowMoveEvent::WindowMoveEvent(int x, int y) : x(x), y(y) {}

	WindowFocusEvent::WindowFocusEvent(bool f) : focused(f) {}
	WindowFocusEvent::operator std::string() const {
		char c = static_cast<char>(focused) + '0';
		return std::string(1, c);
	}
} // namespace EngineThingy
