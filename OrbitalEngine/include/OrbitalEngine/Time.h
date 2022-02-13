#pragma once

namespace OrbitalEngine
{
	class Time
	{
	public: 
		Time(): m_nanoseconds(Time::Now()) { }
		Time(float t): m_nanoseconds(t) { }

		float seconds() { return m_nanoseconds / 1000000000.0f; }
		float milliseconds() { return m_nanoseconds / 1000000.0f; }
		float microseconds() { return m_nanoseconds / 1000.0f; }
		float nanoseconds() { return m_nanoseconds; }

		inline static float Now()
		{
			return static_cast<float>(std::chrono::duration_cast<std::chrono::nanoseconds>(
				std::chrono::system_clock::now().time_since_epoch()
				).count() - s_origin);
		}

		inline static uint64_t Origin() { return s_origin;  }

		operator float() const { return m_nanoseconds; }
		Time operator+(const Time& t) { return Time(m_nanoseconds + (float)t); }
		Time operator*(const Time& t) { return Time(m_nanoseconds * (float)t); }
		Time operator/(const Time& t) { return Time(m_nanoseconds / (float)t); }

	private:
		inline static uint64_t s_origin = std::chrono::duration_cast<std::chrono::nanoseconds>(
			std::chrono::system_clock::now().time_since_epoch()).count();

		float m_nanoseconds;
	};
}