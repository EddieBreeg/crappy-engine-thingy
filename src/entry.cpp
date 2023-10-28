#include <et/entry.hpp>
#include <et/rng.hpp>
#include <et/events/application.hpp>
#include <et/events/window.hpp>
#include <et/events/keyboard.hpp>
#include <et/window_system.hpp>
#include <et/scene_system.hpp>
#include <csignal>

#if defined(ET_DEBUG)
#include <cpptrace/cpptrace.hpp>
#include <iostream>

void crash_handler(int) {
	ET_CORE_LOG_FATAL("Application crashed");
	cpptrace::generate_trace().print(std::cerr);
	debug_break();
}
#endif

#if defined(ET_CONSOLE_MODE)
void interrupt_handler(int) {
	EngineThingy::EventSystem::Instance().EnqueueEvent(
		std::make_unique<EngineThingy::ApplicationQuitEvent>());
}
#endif

namespace EngineThingy {
	using AppArgs_t = libstra::array_view<const char *>;
	Application::Application(AppArgs_t args) : _args(args) {
		ET_ASSERT(!_instance);
		_instance = this;
		RNG::Init();
		LogSystem::Init();
		EventSystem::Init();
		WindowSystem::Init();
		SceneSystem::Init();
		ET_CORE_LOG_INFO("All core systems initialized");
		RegisterSystems<EventSystem, SceneSystem, WindowSystem>();
#ifdef ET_DEBUG
		signal(SIGSEGV, crash_handler);
		signal(SIGABRT, crash_handler);
#endif
#ifdef ET_CONSOLE_MODE
		signal(SIGINT, interrupt_handler);
#endif
	}

	void Application::Run() {
		WindowSystem::Instance().CreateWindow(1280, 720, "ET",
											  WindowFlags::Resizable);
		LogSystem::Instance().SetLevel(spdlog::level::trace);
		_startTime = Clock::now();
		auto &eventSystem = EventSystem::Instance();
		eventSystem.AddListener<ApplicationQuitEvent>(
			[this](const ApplicationQuitEvent &) {
				ET_CORE_LOG_INFO("Received application quit event");
				this->Stop();
			});
		eventSystem.AddListener<WindowCloseEvent>(
			[this](const WindowCloseEvent &) {
				ET_CORE_LOG_INFO("Received window close event");
				this->Stop();
			});
		eventSystem.AddListener<WindowFocusEvent>(
			[](const WindowFocusEvent &evt) {
				if (evt.focused) ET_CORE_LOG_TRACE("Window gained focus");
				else ET_CORE_LOG_TRACE("Window lost focus");
			});
		TimePoint t;
		Timing delta{ 0 };
		while (_run) {
			t = Clock::now();
			Update(delta);
			delta = Clock::now() - t;
		}
	}
	void Application::Update(Timing delta) {
		for (const SystemInstance &sys : _systems)
			sys.Update(delta);
	}

	Application::~Application() {}
} // namespace EngineThingy
