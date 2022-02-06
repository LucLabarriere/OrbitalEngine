#pragma once

#include <format>
#include "OrbitalEngine/Time.h"

namespace OrbitalEngine
{
	class Logger
	{
	public:
		enum class Level
		{
			Debug,
			Info,
			Warn,
			Error,
			Disabled
		};

	public:
		static void SetLevel(Level level)
		{
			s_level = level;
		}

		template <typename ...Args>
		static void Debug(std::string msg, Args... args)
		{
			if (s_level <= Level::Debug)
			{
				Echo(Now() + " " + Bright() + "Orbital" + Reset() + " [" + Green() + "Debug" + Reset() + "] "
					+ msg + EOL(), args...);
			}
		}

		template <typename ...Args>
		static void Info(std::string msg, Args... args)
		{
			if (s_level <= Level::Info)
			{
				Echo(Now() + " " + Bright() + "Orbital" + Reset() + " [" + Blue() + "Info" + Reset() + "] "
					+ msg + EOL(), args...);
			}
		}

		template <typename ...Args>
		static void Warn(std::string msg, Args... args)
		{
			if (s_level <= Level::Warn)
			{
				Echo(Now() + " " + Bright() + "Orbital" + Reset() + " [" + Yellow() + "Warning" + Reset() + "] "
					+ msg + EOL(), args...);
			}
		}

		template <typename ...Args>
		static void Error(std::string msg, Args... args)
		{
			if (s_level <= Level::Error)
			{
				Echo(Now() + " " + Bright() + "Orbital" + Reset() + " [" + Red() + "Error" + Reset() + "] "
					+ msg + EOL(), args...);
			}
		}

		template <typename ...Args>
		static void Critical(std::string msg, Args... args)
		{
			Echo(Now() + " " + Bright() + Red() + "Orbital" + " [CRITICAL] "
				+ msg + EOL(), args...);
		}

		static std::string EOL() { return Reset() + "\n"; }
		static std::string Reset() { return "\033[0m"; }
		static std::string Blue() { return "\033[34m"; }
		static std::string Green() { return "\033[32m"; }
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
		static void Echo(const std::string& msg, Args... args) { std::cout << std::format(msg, args...); }

		static inline Level s_level = Level::Info;
	};
}