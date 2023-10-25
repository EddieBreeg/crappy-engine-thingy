#pragma once

#include "core.hpp"
#include <spdlog/spdlog.h>
#include "singleton.hpp"

namespace EngineThingy {

	class ET_API LogSystem : public Singleton<LogSystem *> {
		LogSystem(spdlog::level::level_enum level);
		std::shared_ptr<spdlog::logger> _coreLogger, _clientLogger;

	public:
		void Update(Timing) const {}
		static LogSystem &Init();

#ifdef ET_BUILD

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
		void ClientInfo(Msg &&message) {
			_clientLogger->info(std::forward<Msg>(message));
		}
		template <class Msg>
		void ClientWarn(Msg &&message) {
			_clientLogger->warn(std::forward<Msg>(message));
		}
		template <class Msg>
		void ClientError(Msg &&message) {
			_clientLogger->error(std::forward<Msg>(message));
		}
		template <class Msg>
		void ClientFatal(Msg &&message) {
			_clientLogger->critical(std::forward<Msg>(message));
		}

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