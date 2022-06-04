#pragma once

namespace Orbital
{
	class Time
	{
	public: 
		Time(): mNanoseconds(Time::Now()) { }
		Time(float t): mNanoseconds(t) { }

		float Seconds() const { return mNanoseconds / 1000000000.0f; }
		float Milliseconds() const { return mNanoseconds / 1000000.0f; }
		float Microseconds() const { return mNanoseconds / 1000.0f; }
		float Nanoseconds() const { return mNanoseconds; }

		inline static float Now()
		{
			return static_cast<float>(std::chrono::duration_cast<std::chrono::nanoseconds>(
				std::chrono::system_clock::now().time_since_epoch()
				).count() - sOrigin);
		}

		inline static uint64_t Origin() { return sOrigin;  }

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

		operator float() const { return mNanoseconds; }
		Time& operator-=(const Time& t) { mNanoseconds -= (float)t; return *this; }
		Time operator-(const Time& t) { return Time(mNanoseconds - (float)t); }
		Time& operator+=(const Time& t) { mNanoseconds += (float)t; return *this; }
		Time operator+(const Time& t) { return Time(mNanoseconds + (float)t); }
		Time& operator*=(const Time& t) { mNanoseconds *= (float)t; return *this; }
		Time operator*(const Time& t) { return Time(mNanoseconds * (float)t); }
		Time& operator/=(const Time& t) { mNanoseconds /= (float)t; return *this; }
		Time operator/(const Time& t) { return Time(mNanoseconds / (float)t); }

	private:
		inline static uint64_t sOrigin = std::chrono::duration_cast<std::chrono::nanoseconds>(
			std::chrono::system_clock::now().time_since_epoch()).count();

		float mNanoseconds;
	};
}