#pragma once

#include "core.hpp"
#include <spdlog/spdlog.h>
#include "singleton.hpp"

namespace EngineThingy {

	class LogSystem : public Singleton<LogSystem *> {
		LogSystem(spdlog::level::level_enum level);
		std::shared_ptr<spdlog::logger> _coreLogger, _clientLogger;

	public:
		void Update(Timing) const {}
		static LogSystem &Init();

#ifdef ET_BUILD
		void CoreInfo(std::string_view message);
		void CoreWarn(std::string_view message);
		void CoreError(std::string_view message);
		void CoreFatal(std::string_view message);
#endif
		void ClientInfo(std::string_view message);
		void ClientWarn(std::string_view message);
		void ClientError(std::string_view message);
		void ClientFatal(std::string_view message);

		~LogSystem();
	};

} // namespace EngineThingy
