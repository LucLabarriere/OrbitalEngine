#pragma once

#include "OrbitalEngine/Utils/Time.h"
#include "OrbitalEngine/Utils/Logger.h"



namespace OrbitalEngine
{

	enum class Metric
	{
		FrameRate = 0,
		ApproximateFrameRate,
		TimePerFrame,
		ApproximateTimePerFrame,
		BatchCount

	};

	static inline std::map<Metric, std::string> MetricNames = {
		{ Metric::FrameRate,					"FrameRate" },
		{ Metric::ApproximateFrameRate,			"ApproximateFrameRate" },
		{ Metric::TimePerFrame,					"TimePerFrame" },
		{ Metric::ApproximateTimePerFrame,		"ApproximateTimePerFrame" },
		{ Metric::BatchCount,					"BatchCount" }
	};

	static inline std::map<Metric, std::string> MetricTypes = {
		{ Metric::FrameRate,					"float" },
		{ Metric::ApproximateFrameRate,			"float" },
		{ Metric::TimePerFrame,					"Time" },
		{ Metric::ApproximateTimePerFrame,		"Time" },
		{ Metric::BatchCount,					"unsigned int" },
	};

	class Metrics
	{
	public:
		static void Initialize() { s_instance = new Metrics; };
		static void OnUpdate(Time dt) { s_instance->onUpdate(dt); };
		template<typename T>
		static T& Get(Metric metric)
		{
			try
			{
				return std::get<T>(s_instance->m_metrics[metric]);
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
		Metrics();
		void onUpdate(Time dt);

	private:
		static inline Metrics* s_instance = nullptr;
		std::vector<Time> m_timePerFrameContainer;
		std::map<Metric, std::variant<Time, unsigned int, float>> m_metrics;
		size_t m_timeIndex = 0;

		Time m_lastUpdatedFrameRate;
	};
}



