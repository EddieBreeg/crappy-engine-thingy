#include <et/window_system.hpp>
#include <et/events/window.hpp>

namespace EngineThingy {
	Window::Window(uint32_t width, uint32_t height, const std::string &title) :
		_size{ width, height }, _title(title) {}

	WindowSystem &WindowSystem::Init() {
		ET_ASSERT(!_instance);
		static WindowSystem s;
		return *(_instance = &s);
	}

	void Window::OnMove(int x, int y) const {
		EventSystem::Instance().EnqueueEvent(
			std::make_unique<WindowMoveEvent>(x, y));
	}
	void Window::OnResize(int x, int y) {
		EventSystem::Instance().EnqueueEvent(
			std::make_unique<WindowResizeEvent>(_size,
												decltype(_size){ x, y }));
		_size = { x, y };
	}
	void Window::OnFocusChange(bool focused) const {
		EventSystem::Instance().EnqueueEvent(
			std::make_unique<WindowFocusEvent>(focused));
	}
	void Window::OnKeyPress(KeyCode k, bool r) const {
		EventSystem::Instance().EnqueueEvent(
			std::make_unique<KeyPressedEvent>(k, r));
	}
	void Window::OnKeyRelease(KeyCode k) const {
		EventSystem::Instance().EnqueueEvent(
			std::make_unique<KeyReleasedEvent>(k));
	}
	void Window::OnMouseButtonPress(MouseButton k) const {
		EventSystem::Instance().EnqueueEvent(
			std::make_unique<MouseButtonPressedEvent>(k));
	}
	void Window::OnMouseButtonRelease(MouseButton k) const {
		EventSystem::Instance().EnqueueEvent(
			std::make_unique<MouseButtonReleasedEvent>(k));
	}
	void Window::OnMouseMove(double x, double y) {
		EventSystem::Instance().EnqueueEvent(
			std::make_unique<CursorMoveEvent>(_mousePos, std::pair{ x, y }));
		_mousePos = { x, y };
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
