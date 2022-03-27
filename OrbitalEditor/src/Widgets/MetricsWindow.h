#pragma once

class MetricsWindow
{
public:
	MetricsWindow() { }

	void render()
	{
		ImGui::Begin("Metrics");

		ImGui::Text("BatchCount: %d", Metrics::Get<unsigned int>(Metric::BatchCount));

		ImGui::End();

	}
};