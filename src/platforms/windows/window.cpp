#include <et/window_system.hpp>
#include <GLFW/glfw3.h>
#include <et/platforms/windows/window.h>

#ifdef ET_WINDOWS

namespace EngineThingy {
	WindowSystem::WindowSystem() {
		ET_ENSURE(glfwInit());
	}
	WindowSystem::~WindowSystem() {
		glfwTerminate();
	}
	WindowImpl::WindowImpl(uint32_t width, uint32_t height,
						   const std::string &title, WindowFlags flags) :
		Window(width, height, title) {}

	WindowImpl::~WindowImpl() {
		glfwDestroyWindow(_win);
	}

	void WindowImpl::Update(Timing) {}
	void WindowImpl::SetVsync(bool VSync) {}
	void WindowImpl::SetResizeable(bool r) {}

	std::unique_ptr<Window>
	Window::Create(uint32_t width, uint32_t height, const std::string &title,
				   WindowFlags flags = WindowFlags::None) {
		WindowImpl *w = new WindowImpl(width, height, title, flags);
		return std::unique_ptr<Window>((Window *)w);
	}
} // namespace EngineThingy

#endif