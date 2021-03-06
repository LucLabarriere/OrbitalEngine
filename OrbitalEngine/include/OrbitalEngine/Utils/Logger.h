#pragma once

#include <fmt/core.h>
#include "OrbitalEngine/Utils/Time.h"

#define OE_TRACE_VARIABLE(var) Logger::Trace(#var": {}", var)

namespace Orbital
{
	class Logger
	{
	public:
		enum class Level
		{
			Trace,
			Debug,
			Info,
			Warn,
			Error,
			Disabled
		};

	public:
		static void SetLevel(Level level)
		{
			sLevel = level;
		}

		template <typename ...Args>
		static void Trace(std::string msg, Args&&... args)
		{
			if (sLevel <= Level::Trace)
			{
				Echo(Now() + " " + Bright() + "Orbital" + Reset() + " [" + Purple() + "Trace  " + Reset() + "] "
					+ msg + EOL(), args...);
			}
		}

		template <typename ...Args>
		static void Debug(std::string msg, Args&&... args)
		{
			if (sLevel <= Level::Debug)
			{
				Echo(Now() + " " + Bright() + "Orbital" + Reset() + " [" + Green() + "Debug  " + Reset() + "] "
					+ msg + EOL(), args...);
			}
		}

		template <typename ...Args>
		static void Info(std::string msg, Args&&... args)
		{
			if (sLevel <= Level::Info)
			{
				Echo(Now() + " " + Bright() + "Orbital" + Reset() + " [" + Cyan() + "Info   " + Reset() + "] "
					+ msg + EOL(), args...);
			}
		}

		template <typename ...Args>
		static void Warn(std::string msg, Args&&... args)
		{
			if (sLevel <= Level::Warn)
			{
				Echo(Now() + " " + Bright() + "Orbital" + Reset() + " [" + Yellow() + "Warning" + Reset() + "] "
					+ msg + EOL(), args...);
			}
		}

		template <typename ...Args>
		static void Error(std::string msg, Args&&... args)
		{
			if (sLevel <= Level::Error)
			{
				Echo(Now() + " " + Bright() + "Orbital" + Reset() + " [" + Red() + "Error  " + Reset() + "] "
					+ msg + EOL(), args...);
			}
		}

		template <typename ...Args>
		[[ noreturn ]] static void Critical(std::string msg, Args&&... args)
		{
			Echo(Now() + " " + Bright() + Red() + "Orbital" + " [CRITICAL] "
				+ msg + EOL(), args...);
		}

		static std::string EOL() { return Reset() + "\n"; }
		static std::string Reset() { return "\033[0m"; }
		static std::string Blue() { return "\033[34m"; }
		static std::string Cyan() { return "\033[36m"; }
		static std::string Green() { return "\033[32m"; }
		static std::string Purple() { return "\033[38;2;150;0;255m"; }
		static std::string Red() { return "\033[31m"; }
		static std::string Yellow() { return "\033[33m"; }
		static std::string Magenta() { return "\033[35m"; }
		static std::string Bright() { return "\033[1m"; }
		static std::string Underline() { return "\033[4m"; }
		static std::string Now()
		{
			auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
			std::tm tm = *std::localtime(&now);
			char buffer[80];
			std::strftime(buffer, sizeof(buffer), "[%H:%M:%S]", &tm);

			return buffer;
		}
		
		template <typename ...Args>
		static void Echo(std::string&& msg, Args&&... args) 
		{ 
			std::cout << fmt::vformat(msg,
				fmt::make_format_args(std::forward<Args>(args)...));
		}

		static inline Level sLevel = Level::Info;
	};
}
