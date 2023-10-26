#pragma once

#include "core.hpp"
#include <spdlog/spdlog.h>
#include "singleton.hpp"

namespace EngineThingy {

	class ET_API LogSystem : public Singleton<LogSystem *> {
		LogSystem(spdlog::level::level_enum level);
		std::shared_ptr<spdlog::logger> _coreLogger, _clientLogger;

	public:
		static LogSystem &Init();
		void SetLevel(spdlog::level::level_enum lvl);

#ifdef ET_BUILD

		template <class Msg>
		void CoreTrace(Msg &&message) {
			_coreLogger->trace(std::forward<Msg>(message));
		}
		template <class Msg>
		void CoreInfo(Msg &&message) {
			_coreLogger->info(std::forward<Msg>(message));
		}
		template <class Msg>
		void CoreWarn(Msg &&message) {
			_coreLogger->warn(std::forward<Msg>(message));
		}
		template <class Msg>
		void CoreError(Msg &&message) {
			_coreLogger->error(std::forward<Msg>(message));
		}
		template <class Msg>
		void CoreFatal(Msg &&message) {
			_coreLogger->critical(std::forward<Msg>(message));
		}
#endif
		template <class Msg>
		void Trace(Msg &&message) {
			_clientLogger->trace(std::forward<Msg>(message));
		}
		template <class Msg>
		void Info(Msg &&message) {
			_clientLogger->info(std::forward<Msg>(message));
		}
		template <class Msg>
		void Warn(Msg &&message) {
			_clientLogger->warn(std::forward<Msg>(message));
		}
		template <class Msg>
		void Error(Msg &&message) {
			_clientLogger->error(std::forward<Msg>(message));
		}
		template <class Msg>
		void Fatal(Msg &&message) {
			_clientLogger->critical(std::forward<Msg>(message));
		}

		~LogSystem();
	};

} // namespace EngineThingy

#ifdef ET_DEBUG
#define ET_LOG_TRACE(x) EngineThingy::LogSystem::Instance().Trace(x)
#define ET_LOG_INFO(x) EngineThingy::LogSystem::Instance().Info(x)
#define ET_LOG_WARN(x) EngineThingy::LogSystem::Instance().Warn(x)
#define ET_LOG_ERROR(x) EngineThingy::LogSystem::Instance().Error(x)
#define ET_LOG_FATAL(x) EngineThingy::LogSystem::Instance().Fatal(x)
#ifdef ET_BUILD
#define ET_CORE_LOG_TRACE(x) EngineThingy::LogSystem::Instance().CoreTrace(x)
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