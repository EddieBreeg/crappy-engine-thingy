#include "system.hpp"
#include <libstra/views.hpp>
#include <vector>
#include "logsystem.hpp"
#include <et/events/event_system.hpp>

namespace EngineThingy {
	class Application;
} // namespace EngineThingy

namespace EngineThingy {

	class ET_API Application : Singleton<Application *> {
	protected:
		libstra::array_view<const char *> _args;
		Application(libstra::array_view<const char *> args);
		virtual void OnStart() {}

	private:
		std::vector<SystemInstance> _systems;
		bool _run = true;
		TimePoint _startTime;

		void Update(Timing delta);

		template <class First, class Second, class... N>
		void RegisterSystem() {
			_systems.emplace_back(SystemInstance::Create<First>());
			RegisterSystem<Second, N...>();
		}

	public:
		void Run();
		void Stop() { _run = false; }
		libstra::array_view<const char *> Args() const { return _args; }

		template <class S>
		void RegisterSystem() {
			_systems.emplace_back(SystemInstance::Create<S>());
		}
		template <class... S>
		void RegisterSystems() {
			if constexpr (!sizeof...(S)) return;
			_systems.reserve(sizeof...(S) + _systems.size());
			RegisterSystem<S...>();
		}

		Application(Application &) = delete;

		virtual ~Application();
	};

} // namespace EngineThingy
