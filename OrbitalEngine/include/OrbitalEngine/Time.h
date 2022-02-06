#pragma once

namespace OrbitalEngine
{
	class Time
	{
	public: 
		Time(): m_microseconds(Time::Now()) { }
		Time(float t): m_microseconds(t) { }

		float seconds() { return m_microseconds / 1000000.0f; }
		float milliseconds() { return m_microseconds / 1000.0f; }
		float microseconds() { return m_microseconds; }

		inline static float Now()
		{
			return static_cast<float>(std::chrono::duration_cast<std::chrono::microseconds>(
				std::chrono::system_clock::now().time_since_epoch()
				).count() - s_origin);
		}

		inline static uint64_t Origin() { return s_origin;  }

		operator float() const { return m_microseconds; }
		Time operator+(const Time& t) { return Time(m_microseconds + (float)t); }
		Time operator*(const Time& t) { return Time(m_microseconds * (float)t); }
		Time operator/(const Time& t) { return Time(m_microseconds / (float)t); }

	private:
		inline static uint64_t s_origin = std::chrono::duration_cast<std::chrono::microseconds>(
			std::chrono::system_clock::now().time_since_epoch()).count();

		float m_microseconds;
	};
}