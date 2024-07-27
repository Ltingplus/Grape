
#include "gppch.h"

#include "Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace Grape
{
	std::shared_ptr<spdlog::logger> Log::s_coreLogger;
	std::shared_ptr<spdlog::logger> Log::s_clientLogger;

	Grape::Log::Log()
	{

	}

	Grape::Log::~Log()
	{

	}

	void Log::Init()
	{
		// change log pattern
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_coreLogger = spdlog::stdout_color_mt("Grape");
		s_coreLogger->set_level(spdlog::level::trace);

		s_clientLogger = spdlog::stdout_color_mt("App");
		s_clientLogger->set_level(spdlog::level::trace);
	}
}
