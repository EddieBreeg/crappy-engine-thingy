#include <et/entry.hpp>

int ET_API main(int argc, char const *argv[]) {
	using namespace EngineThingy;
	auto &app = Application::Init({ argv, argv + argc });
	app.RegisterSystem<LogSystem>();
	ET_CORE_LOG_INFO("Log system initialized");
	app.Run();
	return 0;
}

namespace EngineThingy {
	using AppArgs_t = libstra::array_view<const char *>;
	Application::Application(AppArgs_t args) : _args(args) {}

	Application &Application::Init(AppArgs_t args) {
		ET_ENSURE(!_instance);
		auto *app = new Application(args);
		return *(_instance = std::unique_ptr<Application>(app));
	}
	void Application::Run() {
		_startTime = Clock::now();
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
