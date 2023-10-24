#include <et/core.hpp>
#include <et/logsystem.hpp>
#include <sstream>

namespace EngineThingy {
	void ensure_impl(bool expr, const char *line, const char *file,
					 int lineNumber) {
		if (expr) return;
		std::stringstream ss;
		ss << "Assertion \"" << line << "\" failed at " << file << ':'
		   << lineNumber;
		ET_CORE_LOG_FATAL(ss.str());
		abort();
	}

} // namespace EngineThingy
