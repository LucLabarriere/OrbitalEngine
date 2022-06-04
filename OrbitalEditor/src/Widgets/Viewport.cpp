#include "Viewport.h"
#include "EditorApplication.h"
#include "Tools.h"

Viewport::Viewport(EditorApplication* app)
	: mApp(app)
{

}

void Viewport::Render()
{
	ImGui::GetStyle().WindowPadding = ImVec2(0, 0);

	bool p_open = true;
	ImGui::Begin("Scene viewport", &p_open, ImGuiWindowFlags_MenuBar);

	if (ImGui::BeginMenuBar())
	{
		if (mApp->IsPlaying())
		{
			bool stopButton = Tools::RenderIconButton(TextureIconIndex::Stop);

			if (stopButton)
				mApp->Stop();
		}
		else
		{
			bool playButton = Tools::RenderIconButton(TextureIconIndex::Play);

			if (playButton)
				mApp->Play();
		}

		ImGui::EndMenuBar();
	}

	auto windowSize = ImGui::GetContentRegionAvail();

	if (windowSize[0] <= 10.0f || windowSize[1] <= 10.0f)
	{
		windowSize[0] = 15.0f;
		windowSize[1] = 15.0f;
	}

	mApp->CheckRenderAreaSize(windowSize[0], windowSize[1]);

	ImGui::Image(
		(void*)(size_t)Orbital::Renderer::GetFrame(), windowSize, ImVec2(0, 1), ImVec2(1, 0)
	);


	ImGui::End();
	ImGui::GetStyle().WindowPadding = ImVec2(12, 12);
}