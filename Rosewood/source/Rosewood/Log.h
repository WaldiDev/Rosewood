#pragma once

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace rw
{
	class ROSEWOOD_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return sCoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return sClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> sCoreLogger;
		static std::shared_ptr<spdlog::logger> sClientLogger;
	};
}

#define RW_CORE_TRACE(...) ::rw::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define RW_CORE_INFO(...)  ::rw::Log::GetCoreLogger()->info(__VA_ARGS__)
#define RW_CORE_WARN(...)  ::rw::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define RW_CORE_ERROR(...) ::rw::Log::GetCoreLogger()->error(__VA_ARGS__)
#define RW_CORE_FATAL(...) ::rw::Log::GetCoreLogger()->fatal(__VA_ARGS__)

#define RW_TRACE(...) ::rw::Log::GetClientLogger()->trace(__VA_ARGS__)
#define RW_INFO(...)  ::rw::Log::GetClientLogger()->info(__VA_ARGS__)
#define RW_WARN(...)  ::rw::Log::GetClientLogger()->warn(__VA_ARGS__)
#define RW_ERROR(...) ::rw::Log::GetClientLogger()->error(__VA_ARGS__)
#define RW_FATAL(...) ::rw::Log::GetClientLogger()->fatal(__VA_ARGS__)