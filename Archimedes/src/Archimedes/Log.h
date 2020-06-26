#pragma once

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"

namespace AC {

	class AC_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

// Core log macros
#define AC_CORE_TRACE(...)    ::AC::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define AC_CORE_INFO(...)     ::AC::Log::GetCoreLogger()->info(__VA_ARGS__)
#define AC_CORE_WARN(...)     ::AC::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define AC_CORE_ERROR(...)    ::AC::Log::GetCoreLogger()->error(__VA_ARGS__)
#define AC_CORE_FATAL(...)    ::AC::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define AC_TRACE(...)	      ::AC::Log::GetClientLogger()->trace(__VA_ARGS__)
#define AC_INFO(...)	      ::AC::Log::GetClientLogger()->info(__VA_ARGS__)
#define AC_WARN(...)	      ::AC::Log::GetClientLogger()->warn(__VA_ARGS__)
#define AC_ERROR(...)	      ::AC::Log::GetClientLogger()->error(__VA_ARGS__)
#define AC_FATAL(...)	      ::AC::Log::GetClientLogger()->fatal(__VA_ARGS__) 