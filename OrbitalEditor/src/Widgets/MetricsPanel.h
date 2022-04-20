#pragma once

#include "OrbitalEngine/Utils.h"

using namespace Orbital;

class MetricsPanel
{
public:
	MetricsPanel() { }

	void render()
	{
		bool vsyncEnabled = Metrics::Get<bool>(Metric::VSyncEnabled);

		ImGui::Begin("Metrics");
		ImGui::Checkbox("Show demo Panel", &m_isDemoShown);
		ImGui::Text("Time per frame %.2f ms", Metrics::Get<Time>(Metric::ApproximateTimePerFrame).milliseconds());
		ImGui::Text("FPS %.1f", Metrics::Get<float>(Metric::ApproximateFrameRate));
		ImGui::Text("BatchCount: %d", Metrics::Get<unsigned int>(Metric::BatchCount));
		ImGui::Checkbox("VSync enabled", &vsyncEnabled);
		ImGui::End();

		Metrics::setVSyncEnabled(vsyncEnabled);




		if (ImGui::Begin("Batches"))
		{

		}
		ImGui::End();
	}

	bool isDemoShown() const { return m_isDemoShown; }

private:
	bool m_isDemoShown = true;
};