#pragma once

#include <et/core.hpp>

#ifdef ET_WINDOWS

namespace EngineThingy {
	class ET_API WindowImpl : public Window {
	private:
		struct GLFWwindow *_win = nullptr;
		static void sizeCallback(GLFWwindow *, int w, int h);
		static void moveCallback(GLFWwindow *, int w, int h);
		static void focusCallback(GLFWwindow *, int focused);
		static void mouseButtonCallback(GLFWwindow *, int btn, int action,
										int mods);
		static void mouseMoveCallback(GLFWwindow *, double x, double y);
		static void keyCallback(GLFWwindow *, int k, int scancode, int action,
								int mods);

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