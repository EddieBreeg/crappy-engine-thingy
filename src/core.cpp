#include <et/core.hpp>
#include <et/logsystem.hpp>
#include <sstream>

#ifdef ET_DEBUG

#ifdef ET_CONSOLE_MODE
#include <iostream>
#endif

#include <cpptrace/cpptrace.hpp>
#include <et/events/event_system.hpp>

namespace EngineThingy {
	void ensure_impl(bool expr, const char *line, const char *file,
					 int lineNumber) {
		if (expr) return;
		std::stringstream ss;
		ss << "Assertion \"" << line << "\" failed at " << file << ':'
		   << lineNumber;
		ET_CORE_LOG_FATAL(ss.str());
		cpptrace::generate_trace().print(std::cerr);
		abort();
	}

} // namespace EngineThingy

#endif