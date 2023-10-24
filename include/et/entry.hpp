#include "system.hpp"
#include <libstra/views.hpp>
#include <vector>
#include "logsystem.hpp"

namespace EngineThingy {

	class Application {
	private:
		libstra::array_view<const char *> _args;
		Application(libstra::array_view<const char *> args);
		static std::unique_ptr<Application> _instance;
		std::vector<SystemInstance> _systems;
		bool _run = true;

		void Update(Timing delta);

		template <class First, class Second, class... N>
		void RegisterSystem() {
			_systems.emplace_back(SystemInstance::Create<First>());
			RegisterSystem<Second, N...>();
		}

	public:
		static Application &Init(libstra::array_view<const char *> args);
		static Application &Instance();
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

		~Application();
	};

} // namespace EngineThingy
