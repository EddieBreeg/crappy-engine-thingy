#pragma once

#include <et/core.hpp>
#include <GLFW/glfw3.h>

#ifdef ET_WINDOWS

namespace EngineThingy {
	class ET_API WindowImpl : public Window {
	private:
		GLFWwindow *_win = nullptr;
		static void sizeCallback(GLFWwindow *, int w, int h);
		static void moveCallback(GLFWwindow *, int w, int h);
		static void focusCallback(GLFWwindow *, int focused);

	public:
		WindowImpl(uint32_t width, uint32_t height, const std::string &title,
				   WindowFlags flags);
		~WindowImpl();

		virtual void Update(Timing t) override;
		virtual void SetVsync(bool) override;
		virtual void SetResizeable(bool) override;
	};
} // namespace EngineThingy

#endif