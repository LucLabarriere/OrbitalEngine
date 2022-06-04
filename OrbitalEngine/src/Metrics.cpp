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
		: mTimePerFrameContainer(10)
	{
		mMetrics[Metric::FrameRate] = (float)0.0f;
		mMetrics[Metric::ApproximateFrameRate] = (float)0.0f;
		mMetrics[Metric::TimePerFrame] = Time();
		mMetrics[Metric::ApproximateTimePerFrame] = Time();
		mMetrics[Metric::BatchCount] = (unsigned int)0;
		mMetrics[Metric::VSyncEnabled] = (bool)true;
	}

	void Metrics::OnUpdateImpl(Time dt)
	{
		mLastUpdatedFrameRate += dt;

		if (mTimeIndex == mTimePerFrameContainer.size())
			mTimeIndex = 0;

		mTimePerFrameContainer[mTimeIndex] = dt;

		float average = 0;
		for (auto& t : mTimePerFrameContainer)
		{
			average += t.Seconds();
		}

		average = average / mTimePerFrameContainer.size();

		mMetrics[Metric::TimePerFrame] = dt;
		mMetrics[Metric::FrameRate] = 1 / dt.Seconds();

		if (mLastUpdatedFrameRate.Milliseconds() > 60.0f)
		{
			mMetrics[Metric::ApproximateTimePerFrame] = Time::FromSeconds(average);
			mMetrics[Metric::ApproximateFrameRate] = 1 / Metrics::Get<Time>(Metric::ApproximateTimePerFrame).Seconds();
			mLastUpdatedFrameRate = Time(0);
		}

		mTimeIndex += 1;
	}
}