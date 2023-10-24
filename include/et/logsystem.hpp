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

#ifdef ET_DEBUG
#define ET_LOG_INFO(x) EngineThingy::LogSystem::Instance().ClientInfo(x)
#define ET_LOG_WARN(x) EngineThingy::LogSystem::Instance().ClientWarn(x)
#define ET_LOG_ERROR(x) EngineThingy::LogSystem::Instance().ClientError(x)
#define ET_LOG_FATAL(x) EngineThingy::LogSystem::Instance().ClientFatal(x)
#ifdef ET_BUILD
#define ET_CORE_LOG_INFO(x) EngineThingy::LogSystem::Instance().CoreInfo(x)
#define ET_CORE_LOG_WARN(x) EngineThingy::LogSystem::Instance().CoreWarn(x)
#define ET_CORE_LOG_ERROR(x) EngineThingy::LogSystem::Instance().CoreError(x)
#define ET_CORE_LOG_FATAL(x) EngineThingy::LogSystem::Instance().CoreFatal(x)
#endif
#else
#define ET_LOG_INFO(x) 0
#define ET_LOG_WARN(x) 0
#define ET_LOG_ERROR(x) 0
#define ET_LOG_FATAL(x) 0
#define ET_CORE_LOG_INFO(x) 0
#define ET_CORE_LOG_WARN(x) 0
#define ET_CORE_LOG_ERROR(x) 0
#define ET_CORE_LOG_FATAL(x) 0
#endif