#include <et/entry.hpp>
#include <et/rng.hpp>
#include <et/events/application.hpp>
#include <et/events/window.hpp>
#include <et/window_system.hpp>
#include <csignal>

#ifdef ET_CONSOLE_MODE
void interrupt_handler(int) {
	EngineThingy::EventSystem::Instance().EnqueueEvent(
		std::make_unique<EngineThingy::ApplicationQuitEvent>());
}
#endif

int ET_API main(int argc, char const *argv[]) {
	using namespace EngineThingy;
	auto &app = Application::Init({ argv, argv + argc });
	app.RegisterSystems<LogSystem, EventSystem, WindowSystem>();
	ET_CORE_LOG_INFO("All major systems initialized");
#ifdef ET_CONSOLE_MODE
	std::signal(SIGINT, interrupt_handler);
#endif
	WindowSystem::Instance().CreateWindow(1280, 720, "ET");
	app.Run();
	return 0;
}

namespace EngineThingy {
	using AppArgs_t = libstra::array_view<const char *>;
	Application::Application(AppArgs_t args) : _args(args) {
		RNG::Init();
	}

	Application &Application::Init(AppArgs_t args) {
		ET_ENSURE(!_instance);
		auto *app = new Application(args);
		return *(_instance = std::unique_ptr<Application>(app));
	}

	void Application::Run() {
		_startTime = Clock::now();
		auto &eventSystem = EventSystem::Instance();
		eventSystem.AddListener<ApplicationStartEvent>(
			[](const ApplicationStartEvent &) {
				ET_CORE_LOG_INFO("Application start event received");
			});
		eventSystem.EnqueueEvent(std::make_unique<ApplicationStartEvent>());

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
