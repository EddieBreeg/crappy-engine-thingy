#pragma once

#include <et/core.hpp>

#ifdef ET_WINDOWS

struct HWND__;

namespace EngineThingy {
	class ET_API WindowImpl : public Window {
	private:
		HWND__ *_win = nullptr;
		static int64_t proc(HWND__ *, unsigned, uint64_t, int64_t);

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