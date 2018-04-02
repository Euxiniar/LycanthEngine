#pragma once

#include <string>

namespace Ly {
	class Log {
	public:
		static void info(const std::string message);
		static void debug(const std::string message);
		static void error(const std::string message);
	};
}