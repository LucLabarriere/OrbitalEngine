#pragma once

class MetricsPanel
{
public:
	MetricsPanel() { }

	void render()
	{
		ImGui::Begin("Metrics");
		ImGui::Checkbox("Show demo Panel", &m_isDemoShown);
		ImGui::Text("Time per frame %.2f ms", Metrics::Get<Time>(Metric::ApproximateTimePerFrame).milliseconds());
		ImGui::Text("FPS %.1f", Metrics::Get<float>(Metric::ApproximateFrameRate));
		ImGui::Text("BatchCount: %d", Metrics::Get<unsigned int>(Metric::BatchCount));
		ImGui::End();
	}

	bool isDemoShown() const { return m_isDemoShown; }

private:
	bool m_isDemoShown = true;
};