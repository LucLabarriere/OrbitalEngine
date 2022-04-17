#include "OrbitalEngine/Utils/Metrics.h"

namespace Orbital
{
	void Metrics::IncrementBatchCount()
	{
		GetReference<unsigned int>(Metric::BatchCount) += 1;
	}

	void Metrics::ReinitializeBatchCount()
	{
		GetReference<unsigned int>(Metric::BatchCount) = -1;
	}

	Metrics::Metrics()
		: m_timePerFrameContainer(10)
	{
		m_metrics[Metric::FrameRate] = (float)0.0f;
		m_metrics[Metric::ApproximateFrameRate] = (float)0.0f;
		m_metrics[Metric::TimePerFrame] = Time();
		m_metrics[Metric::ApproximateTimePerFrame] = Time();
		m_metrics[Metric::BatchCount] = (unsigned int)0;
		m_metrics[Metric::VSyncEnabled] = (bool)true;
	}

	void Metrics::onUpdate(Time dt)
	{
		m_lastUpdatedFrameRate += dt;

		if (m_timeIndex == m_timePerFrameContainer.size())
			m_timeIndex = 0;

		m_timePerFrameContainer[m_timeIndex] = dt;

		float average = 0;
		for (auto& t : m_timePerFrameContainer)
		{
			average += t.seconds();
		}

		average = average / m_timePerFrameContainer.size();

		m_metrics[Metric::TimePerFrame] = dt;
		m_metrics[Metric::FrameRate] = 1 / dt.seconds();

		if (m_lastUpdatedFrameRate.milliseconds() > 60.0f)
		{
			m_metrics[Metric::ApproximateTimePerFrame] = Time::FromSeconds(average);
			m_metrics[Metric::ApproximateFrameRate] = 1 / Metrics::Get<Time>(Metric::ApproximateTimePerFrame).seconds();
			m_lastUpdatedFrameRate = Time(0);
		}

		m_timeIndex += 1;
	}
}