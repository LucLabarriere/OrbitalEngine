#pragma once

#include "OrbitalEngine/Utils/Time.h"
#include "OrbitalEngine/Utils/Logger.h"

namespace Orbital
{

	enum class Metric
	{
		FrameRate = 0,
		ApproximateFrameRate,
		TimePerFrame,
		ApproximateTimePerFrame,
		BatchCount,
		VSyncEnabled
	};

	static inline std::map<Metric, std::string> MetricNames = {
		{ Metric::FrameRate,					"FrameRate" },
		{ Metric::ApproximateFrameRate,			"ApproximateFrameRate" },
		{ Metric::TimePerFrame,					"TimePerFrame" },
		{ Metric::ApproximateTimePerFrame,		"ApproximateTimePerFrame" },
		{ Metric::BatchCount,					"BatchCount" },
		{ Metric::VSyncEnabled,					"VSyncEnabled" }
	};

	static inline std::map<Metric, std::string> MetricTypes = {
		{ Metric::FrameRate,					"float" },
		{ Metric::ApproximateFrameRate,			"float" },
		{ Metric::TimePerFrame,					"Time" },
		{ Metric::ApproximateTimePerFrame,		"Time" },
		{ Metric::BatchCount,					"unsigned int" },
		{ Metric::VSyncEnabled,					"bool" }
	};

	class Metrics
	{
	public:
		static void Initialize() { sInstance = new Metrics; };
		static void OnUpdate(Time dt) { sInstance->OnUpdateImpl(dt); };
		template<typename T>
		static const T& Get(Metric metric)
		{
			try
			{
				return std::get<T>(sInstance->mMetrics[metric]);
			}
			catch (std::bad_variant_access&)
			{
				OE_RAISE_SIGSEGV(
					"Metrics: '{}' must be accessed using 'Metrics::Get<{}>(Metric::{})'",
					MetricNames[metric], MetricTypes[metric], MetricNames[metric]
				);
			}
			OE_RAISE_SIGSEGV("Error, trying to access a non existing metric");
		}
		static void IncrementBatchCount();
		static void ReinitializeBatchCount();
		static void SetVSyncEnabled(bool value) { GetReference<bool>(Metric::VSyncEnabled) = value; }

	private:
		Metrics();
		void OnUpdateImpl(Time dt);

		template<typename T>
		static T& GetReference(Metric metric)
		{
			try
			{
				return std::get<T>(sInstance->mMetrics[metric]);
			}
			catch (std::bad_variant_access&)
			{
				OE_RAISE_SIGSEGV(
					"Metrics: '{}' must be accessed using 'Metrics::Get<{}>(Metric::{})'",
					MetricNames[metric], MetricTypes[metric], MetricNames[metric]
				);
			}
			OE_RAISE_SIGSEGV("Error, trying to access a non existing metric");
		}

	private:
		static inline Metrics* sInstance = nullptr;
		std::vector<Time> mTimePerFrameContainer;
		std::map<Metric, std::variant<Time, unsigned int, float, bool>> mMetrics;
		size_t mTimeIndex = 0;

		Time mLastUpdatedFrameRate;
	};
}



