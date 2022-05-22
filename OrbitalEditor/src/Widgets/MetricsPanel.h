#pragma once

#include "OrbitalEngine/Utils.h"
#include "OrbitalEngine/Graphics/CameraController.h"

using namespace Orbital;

class MetricsPanel
{
public:
	MetricsPanel(Ref<CameraController> cameraController) : m_cameraController(cameraController) { }

	void render()
	{
		bool vsyncEnabled = Metrics::Get<bool>(Metric::VSyncEnabled);

		ImGui::Begin("Metrics");
		ImGui::Checkbox("Show demo Panel", &m_isDemoShown);
		ImGui::Text("Time per frame %.2f ms", Metrics::Get<Time>(Metric::ApproximateTimePerFrame).milliseconds());
		ImGui::Text("FPS %.1f", Metrics::Get<float>(Metric::ApproximateFrameRate));
		ImGui::Text("BatchCount: %d", Metrics::Get<unsigned int>(Metric::BatchCount));
		ImGui::Checkbox("VSync enabled", &vsyncEnabled);
		ImGui::SliderFloat("Camera translation speed", &m_cameraController->getTranslationSpeed(), 0.01f, 50.0f);
		ImGui::SliderFloat("Camera rotation speed", &m_cameraController->getRotationSpeed(), 0.01f, 50.0f);
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
	Ref<CameraController> m_cameraController;
};