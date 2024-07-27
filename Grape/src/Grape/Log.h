#pragma once

#include "Core.h"
// This ignores all warnings raised inside External headers
#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)

namespace Grape
{
	class GRAPE_API Log
	{
	public: 
		static void Init();

		static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_coreLogger; }
		static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_clientLogger; }
		

	private:
		static std::shared_ptr<spdlog::logger> s_coreLogger;
		static std::shared_ptr<spdlog::logger> s_clientLogger;
	};
}


// Core log macros
#define GP_CORE_TRACE(...)    ::Grape::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define GP_CORE_INFO(...)     ::Grape::Log::GetCoreLogger()->info(__VA_ARGS__)
#define GP_CORE_WARN(...)     ::Grape::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define GP_CORE_ERROR(...)    ::Grape::Log::GetCoreLogger()->error(__VA_ARGS__)
#define GP_CORE_CRITICAL(...) ::Grape::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define GP_TRACE(...)         ::Grape::Log::GetClientLogger()->trace(__VA_ARGS__)
#define GP_INFO(...)          ::Grape::Log::GetClientLogger()->info(__VA_ARGS__)
#define GP_WARN(...)          ::Grape::Log::GetClientLogger()->warn(__VA_ARGS__)
#define GP_ERROR(...)         ::Grape::Log::GetClientLogger()->error(__VA_ARGS__)
#define GP_CRITICAL(...)      ::Grape::Log::GetClientLogger()->critical(__VA_ARGS__)

