#include <et/window_system.hpp>

namespace EngineThingy {
	Window::Window(uint32_t width, uint32_t height, const std::string &title) :
		_size{ width, height }, _title(title) {}

	WindowSystem &WindowSystem::Init() {
		ET_ASSERT(!_instance);
		static WindowSystem s;
		return *(_instance = &s);
	}

	Window &WindowSystem::CreateWindow(uint32_t width, uint32_t height,
									   const std::string &title,
									   WindowFlags flags) {
		_window = Window::Create(width, height, title, flags);
		return *_window;
	}

	void WindowSystem::Update(Timing t) {
		ET_ASSERT_ONCE(_window);
		_window->Update(t);
	}
} // namespace EngineThingy
