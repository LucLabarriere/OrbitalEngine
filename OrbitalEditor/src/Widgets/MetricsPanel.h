#pragma once

#include "OrbitalEngine/Utils.h"
#include "OrbitalEngine/Components/Scripts/FreeCameraController.h"

using namespace Orbital;

class MetricsPanel
{
public:
	MetricsPanel(FreeCameraController* cameraController) : mCameraController(cameraController) { }

	void Render()
	{
		bool vsyncEnabled = Metrics::Get<bool>(Metric::VSyncEnabled);

		ImGui::Begin("Metrics");
		ImGui::Checkbox("Show demo Panel", &mIsDemoShown);
		ImGui::Text("Time per frame %.2f ms", Metrics::Get<Time>(Metric::ApproximateTimePerFrame).Milliseconds());
		ImGui::Text("FPS %.1f", Metrics::Get<float>(Metric::ApproximateFrameRate));
		ImGui::Text("BatchCount: %d", Metrics::Get<unsigned int>(Metric::BatchCount));
		ImGui::Checkbox("VSync enabled", &vsyncEnabled);
		ImGui::SliderFloat("Camera translation speed", &mCameraController->GetTranslationSpeed(), 0.01f, 50.0f);
		ImGui::SliderFloat("Camera rotation speed", &mCameraController->GetRotationSpeed(), 0.01f, 50.0f);
		ImGui::End();

		Metrics::SetVSyncEnabled(vsyncEnabled);

		if (ImGui::Begin("Batches"))
		{

		}
		ImGui::End();
	}

	bool IsDemoShown() const { return mIsDemoShown; }

private:
	bool mIsDemoShown = true;
	FreeCameraController* mCameraController;
};