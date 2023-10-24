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

	void LogSystem::CoreInfo(std::string_view msg) {
		_coreLogger->info(msg);
	}
	void LogSystem::CoreWarn(std::string_view msg) {
		_coreLogger->warn(msg);
	}
	void LogSystem::CoreError(std::string_view msg) {
		_coreLogger->error(msg);
	}
	void LogSystem::CoreFatal(std::string_view msg) {
		_coreLogger->critical(msg);
	}

	void LogSystem::ClientInfo(std::string_view msg) {
		_clientLogger->info(msg);
	}
	void LogSystem::ClientWarn(std::string_view msg) {
		_clientLogger->warn(msg);
	}
	void LogSystem::ClientError(std::string_view msg) {
		_clientLogger->error(msg);
	}
	void LogSystem::ClientFatal(std::string_view msg) {
		_clientLogger->critical(msg);
	}

} // namespace EngineThingy
