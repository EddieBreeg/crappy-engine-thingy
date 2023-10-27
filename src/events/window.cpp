#include <et/events/window.hpp>
#include <spdlog/fmt/fmt.h>

namespace EngineThingy {
	WindowResizeEvent::WindowResizeEvent(
		WindowResizeEvent::WindowSize old,
		WindowResizeEvent::WindowSize newSize) :
		oldSize(old), newSize(newSize) {}

	WindowResizeEvent::operator std::string() const {
		return fmt::format("Window resize ({}, {}) -> ({}, {})", oldSize.first,
						   oldSize.second, newSize.first, newSize.second);
	}
	WindowMoveEvent::operator std::string() const {
		return fmt::format("({}, {})", x, y);
	}
	WindowMoveEvent::WindowMoveEvent(int x, int y) : x(x), y(y) {}

	WindowFocusEvent::WindowFocusEvent(bool f) : focused(f) {}
	WindowFocusEvent::operator std::string() const {
		char c = static_cast<char>(focused) + '0';
		return std::string(1, c);
	}
} // namespace EngineThingy
