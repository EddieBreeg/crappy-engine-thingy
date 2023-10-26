#pragma once

#include <et/core.hpp>
#include <et/singleton.hpp>

namespace EngineThingy {
	enum class WindowFlags : uint32_t {
		None = 0,
		Resizable = BIT(0),
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

		void OnMove(int x, int y) const;
		void OnResize(int x, int y);
		void OnFocusChange(bool focused) const;
		void OnKeyPress(int k, bool repeat) const;
		void OnKeyRelease(int k) const;

	public:
		virtual ~Window() = default;
		virtual void Update(Timing) = 0;
		virtual void SetResizeable(bool resizeable) = 0;
		virtual void SetVsync(bool vsync) = 0;
		[[nodiscard]]
		std::pair<uint32_t, uint32_t> GetSize() const noexcept {
			return _size;
		}

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
		Window &GetActive() {
			ET_ASSERT(_window);
			return *_window;
		}

	private:
		WindowSystem();
		std::unique_ptr<Window> _window;
	};
} // namespace EngineThingy
