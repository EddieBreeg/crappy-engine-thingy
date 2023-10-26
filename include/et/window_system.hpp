#pragma once

#include <et/core.hpp>
#include <et/singleton.hpp>

namespace EngineThingy {
	enum class WindowFlags : uint32_t {
		None = 0,
		Resizeable = BIT(0),
		Fullscreen = BIT(1),
		VSync = BIT(2),
	};
	template <WindowFlags F>
	static constexpr WindowFlags BuildWindowFlags() {
		return F;
	}
	template <WindowFlags F, WindowFlags S, WindowFlags... N>
	static constexpr WindowFlags BuildWindowFlags() {
		return ENUM_TO_INT(F) |
			   static_cast<uint32_t>(BuildWindowFlags<S, N...>());
	}
	static constexpr bool CheckWindowFlag(WindowFlags mask, WindowFlags flag) {
		return ENUM_TO_INT(mask) & ENUM_TO_INT(flag);
	}

	class ET_API Window {
	protected:
		std::pair<uint32_t, uint32_t> _size;
		std::string _title;
		Window(uint32_t width, uint32_t height, const std::string &title);

	public:
		virtual ~Window() = default;
		virtual void Update(Timing) = 0;
		virtual void SetResizeable(bool resizeable) = 0;
		virtual void SetVsync(bool vsync) = 0;

		static std::unique_ptr<Window> Create(uint32_t width, uint32_t height,
											  const std::string &title,
											  WindowFlags flags);
	};

	class ET_API WindowSystem : public Singleton<WindowSystem *> {
	public:
		~WindowSystem();
		void Update(Timing);
		static WindowSystem &Init();
		Window &CreateWindow(uint32_t width, uint32_t height,
							 const std::string &title,
							 WindowFlags flags = WindowFlags::None);

	private:
		WindowSystem();
		std::unique_ptr<Window> _window;
	};
} // namespace EngineThingy
