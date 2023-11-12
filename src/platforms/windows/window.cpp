#include <et/window_system.hpp>

#include <d3d11.h>
#include <et/platforms/windows/window.h>
#include <et/events/window.hpp>
#include <et/events/keyboard.hpp>
#include <et/logsystem.hpp>

#ifdef ET_WINDOWS

namespace EngineThingy {

	WindowSystem::WindowSystem() {}

	WindowSystem::~WindowSystem() {}

	LRESULT WindowImpl::proc(HWND native, unsigned msg, WPARAM wp, LPARAM lp) {
		WindowImpl *win =
			reinterpret_cast<WindowImpl *>(GetWindowLongPtr(native, -21));
		switch (msg) {
		case WM_CLOSE:
			EventSystem::Instance().EnqueueEvent(
				EventReference(new WindowCloseEvent{}));
			break;
		case WM_SIZE:
			switch (wp) {
			case SIZE_RESTORED:
				win->OnResize(LOWORD(lp), HIWORD(lp));
				break;
			case SIZE_MINIMIZED:
				break;
			case SIZE_MAXIMIZED:
				break;
			default:
				break;
			}
			break;
		case WM_SETFOCUS:
			win->OnFocusChange(true);
			break;
		case WM_KILLFOCUS:
			win->OnFocusChange(false);
			break;
		case WM_MOVE:
			win->OnMove(LOWORD(lp), HIWORD(lp));
			break;
		case WM_MOUSEMOVE: {
			int x = LOWORD(lp), y = HIWORD(lp);
			win->OnMouseMove(x, y);
			break;
		}
		default:
			break;
		}
		return DefWindowProc(native, msg, wp, lp);
	}

	WindowImpl::WindowImpl(uint32_t width, uint32_t height,
						   const std::string &title, WindowFlags flags) :
		Window(width, height, title) {
		WNDCLASS wc		 = {};
		wc.lpszClassName = "Win32Window";
		wc.hInstance	 = GetModuleHandle(NULL);
		wc.lpfnWndProc	 = proc;
		RegisterClass(&wc);

		DWORD style = WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME;
		if (CheckWindowFlag(flags, WindowFlags::Resizable)) style |= WS_SIZEBOX;

		_win = CreateWindowExA(0, wc.lpszClassName, title.c_str(), style,
							   CW_USEDEFAULT, CW_USEDEFAULT, width, height,
							   NULL, NULL, wc.hInstance, NULL);
		ET_ASSERT(_win);
		SetWindowLongPtr(_win, -21, LONG_PTR(this));
		ShowWindow(_win, 1);
		RECT r;
		GetWindowRect(_win, &r);
		POINT curPos;
		GetCursorPos(&curPos);
		_mousePos = {
			curPos.x - r.left,
			curPos.y - r.top,
		};
	}

	WindowImpl::~WindowImpl() {}

	void WindowImpl::Update(Timing) {
		MSG m;
		while (PeekMessageW(&m, _win, 0, 0, PM_REMOVE)) {
			TranslateMessage(&m);
			DispatchMessage(&m);
		}
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