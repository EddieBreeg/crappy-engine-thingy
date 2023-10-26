#include <et/window_system.hpp>
#include <GLFW/glfw3.h>
#include <et/platforms/windows/window.h>
#include <et/events/window.hpp>

#ifdef ET_WINDOWS

namespace EngineThingy {

	void WindowImpl::sizeCallback(GLFWwindow *ptr, int w, int h) {
		auto *win =
			reinterpret_cast<WindowImpl *>(glfwGetWindowUserPointer(ptr));
		win->OnResize(w, h);
	}
	void WindowImpl::moveCallback(GLFWwindow *ptr, int x, int y) {
		auto *win =
			reinterpret_cast<WindowImpl *>(glfwGetWindowUserPointer(ptr));
		win->OnMove(x, y);
	}
	void WindowImpl::focusCallback(GLFWwindow *ptr, int f) {
		auto *win =
			reinterpret_cast<WindowImpl *>(glfwGetWindowUserPointer(ptr));
		win->OnFocusChange(f);
	}

	WindowSystem::WindowSystem() {
		int success = glfwInit();
		ET_ASSERT(success);
	}
	WindowSystem::~WindowSystem() {
		glfwTerminate();
	}
	WindowImpl::WindowImpl(uint32_t width, uint32_t height,
						   const std::string &title, WindowFlags flags) :
		Window(width, height, title) {
		glfwWindowHint(GLFW_RESIZABLE,
					   CheckWindowFlag(flags, WindowFlags::Resizable));

		_win = glfwCreateWindow(width, height, title.data(),
								CheckWindowFlag(flags, WindowFlags::Fullscreen)
									? glfwGetPrimaryMonitor()
									: NULL,
								NULL);
		ET_ASSERT(_win);
		glfwSetWindowSizeCallback(_win, sizeCallback);
		glfwSetWindowFocusCallback(_win, focusCallback);
		glfwSetWindowPosCallback(_win, moveCallback);
		glfwSetWindowUserPointer(_win, this);
	}

	WindowImpl::~WindowImpl() {
		glfwDestroyWindow(_win);
	}

	void WindowImpl::Update(Timing) {
		glfwPollEvents();
		if (glfwWindowShouldClose(_win)) {
			EventSystem::Instance().EnqueueEvent(
				std::make_unique<WindowCloseEvent>());
		}
		glfwSwapBuffers(_win);
	}
	void WindowImpl::SetVsync(bool VSync) {
		glfwSwapInterval(VSync);
	}
	void WindowImpl::SetResizeable(bool r) {}

	std::unique_ptr<Window>
	Window::Create(uint32_t width, uint32_t height, const std::string &title,
				   WindowFlags flags = WindowFlags::None) {
		WindowImpl *w = new WindowImpl(width, height, title, flags);
		return std::unique_ptr<Window>((Window *)w);
	}
} // namespace EngineThingy

#endif