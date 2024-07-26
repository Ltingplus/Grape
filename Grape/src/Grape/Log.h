#pragma once

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"

namespace Grape
{
	class GRAPE_API Log
	{
	public: 
		Log();
		~Log();

		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger()
		{
			return s_coreLogger;
		}
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger()
		{
			return s_clientLogger;
		}

	private:
		static std::shared_ptr<spdlog::logger> s_coreLogger;
		static std::shared_ptr<spdlog::logger> s_clientLogger;
	};
}

#define GP_CORE_ERROR(...)	::Grape::Log::GetCoreLogger()->error(__VA_ARGS__)
#define GP_CORE_WARN(...)	::Grape::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define GP_CORE_INFO(...)	::Grape::Log::GetCoreLogger()->info(__VA_ARGS__)
#define GP_CORE_TRACE(...)	::Grape::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define GP_CORE_FATAL(...)	::Grape::Log::GetCoreLogger()->fatal(__VA_ARGS__)

#define GP_CLIENT_ERROR(...)	::Grape::Log::GetClientLogger()->error(__VA_ARGS__)
#define GP_CLIENT_WARN(...)		::Grape::Log::GetClientLogger()->warn(__VA_ARGS__)
#define GP_CLIENT_INFO(...)		::Grape::Log::GetClientLogger()->info(__VA_ARGS__)
#define GP_CLIENT_TRACE(...)	::Grape::Log::GetClientLogger()->trace(__VA_ARGS__)
#define GP_CLIENT_FATAL(...)	::Grape::Log::GetClientLogger()->fatal(__VA_ARGS__)