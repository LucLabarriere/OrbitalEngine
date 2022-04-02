#pragma once

namespace Orbital
{
	class Time
	{
	public: 
		Time(): m_nanoseconds(Time::Now()) { }
		Time(float t): m_nanoseconds(t) { }

		float seconds() const { return m_nanoseconds / 1000000000.0f; }
		float milliseconds() const { return m_nanoseconds / 1000000.0f; }
		float microseconds() const { return m_nanoseconds / 1000.0f; }
		float nanoseconds() const { return m_nanoseconds; }

		inline static float Now()
		{
			return static_cast<float>(std::chrono::duration_cast<std::chrono::nanoseconds>(
				std::chrono::system_clock::now().time_since_epoch()
				).count() - s_origin);
		}

		inline static uint64_t Origin() { return s_origin;  }

		inline static Time FromSeconds(float s)
		{
			return Time(s * 1e9f);
		}

		inline static Time FromMilliseconds(float ms)
		{
			return Time(ms * 1e6f);
		}

		inline static Time FromMicroseconds(float us)
		{
			return Time(us * 1e3f);
		}

		operator float() const { return m_nanoseconds; }
		Time& operator-=(const Time& t) { m_nanoseconds -= (float)t; return *this; }
		Time operator-(const Time& t) { return Time(m_nanoseconds - (float)t); }
		Time& operator+=(const Time& t) { m_nanoseconds += (float)t; return *this; }
		Time operator+(const Time& t) { return Time(m_nanoseconds + (float)t); }
		Time& operator*=(const Time& t) { m_nanoseconds *= (float)t; return *this; }
		Time operator*(const Time& t) { return Time(m_nanoseconds * (float)t); }
		Time& operator/=(const Time& t) { m_nanoseconds /= (float)t; return *this; }
		Time operator/(const Time& t) { return Time(m_nanoseconds / (float)t); }

	private:
		inline static uint64_t s_origin = std::chrono::duration_cast<std::chrono::nanoseconds>(
			std::chrono::system_clock::now().time_since_epoch()).count();

		float m_nanoseconds;
	};
}