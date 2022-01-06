#pragma once

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"

namespace LarkinLab
{

	class LL_API Log
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

// Core Log Macros
#define LL_CORE_TRACE(...)	::LarkinLab::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define LL_CORE_INFO(...)	::LarkinLab::Log::GetCoreLogger()->info(__VA_ARGS__)
#define LL_CORE_WARN(...)	::LarkinLab::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define LL_CORE_ERROR(...)	::LarkinLab::Log::GetCoreLogger()->error(__VA_ARGS__)
#define LL_CORE_FATAL(...)	::LarkinLab::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client Log Macros
#define LL_TRACE(...)		::LarkinLab::Log::GetClientLogger()->trace(__VA_ARGS__)
#define LL_INFO(...)		::LarkinLab::Log::GetClientLogger()->info(__VA_ARGS__)
#define LL_WARN(...)		::LarkinLab::Log::GetClientLogger()->warn(__VA_ARGS__)
#define LL_ERROR(...)		::LarkinLab::Log::GetClientLogger()->error(__VA_ARGS__)
#define LL_FATAL(...)		::LarkinLab::Log::GetClientLogger()->fatal(__VA_ARGS__)

