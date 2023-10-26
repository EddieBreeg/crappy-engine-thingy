#include <et/window_system.hpp>
#include <GLFW/glfw3.h>
#include <et/platforms/windows/window.h>
#include <et/events/window.hpp>

#ifdef ET_WINDOWS

namespace EngineThingy {

	void WindowImpl::sizeCallback(GLFWwindow *, int w, int h) {
		WindowImpl &win = (WindowImpl &)WindowSystem::Instance().GetActive();
		EventSystem::Instance().EnqueueEvent(
			std::make_unique<WindowResizeEvent>(win.GetSize(),
												std::pair{ w, h }));
		win._size = std::pair<uint32_t, uint32_t>{ w, h };
	}
	void WindowImpl::focusCallback(GLFWwindow *, int f) {
		EventSystem::Instance().EnqueueEvent(
			std::make_unique<WindowFocusEvent>(bool(f)));
	}

	WindowSystem::WindowSystem() {
		ET_ENSURE(glfwInit());
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
		ET_ENSURE(_win);
		glfwSetWindowSizeCallback(_win, sizeCallback);
		glfwSetWindowFocusCallback(_win, focusCallback);
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