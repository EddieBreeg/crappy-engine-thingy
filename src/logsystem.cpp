#include <et/logsystem.hpp>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace EngineThingy {
	LogSystem::LogSystem(spdlog::level::level_enum lvl) {
		spdlog::set_level(lvl);
		spdlog::set_pattern("%^[%H:%M:%S.%3e] %n:\t%v%$");
		_coreLogger = spdlog::stdout_color_mt("CORE");
		_clientLogger = spdlog::stdout_color_mt("CLIENT");
	}
	LogSystem::~LogSystem() {}

	LogSystem &LogSystem::Init() {
		assert(!_instance);
		static LogSystem ls(spdlog::level::info);
		return *(_instance = &ls);
	}

} // namespace EngineThingy
