#include "Viewport.h"
#include "EditorApplication.h"
#include "Tools.h"

Viewport::Viewport(EditorApplication* app)
	: m_app(app)
{

}

void Viewport::render()
{
	ImGui::GetStyle().WindowPadding = ImVec2(0, 0);

	bool p_open = true;
	ImGui::Begin("Scene viewport", &p_open, ImGuiWindowFlags_MenuBar);

	if (ImGui::BeginMenuBar())
	{
		if (m_app->isPlaying())
		{
			bool stopButton = Tools::RenderIconButton(TextureIconIndex::Stop);

			if (stopButton)
				m_app->stop();
		}
		else
		{
			bool playButton = Tools::RenderIconButton(TextureIconIndex::Play);

			if (playButton)
				m_app->play();
		}

		ImGui::EndMenuBar();
	}

	auto windowSize = ImGui::GetContentRegionAvail();

	if (windowSize[0] <= 10.0f || windowSize[1] <= 10.0f)
	{
		windowSize[0] = 15.0f;
		windowSize[1] = 15.0f;
	}

	m_app->checkRenderAreaSize(windowSize[0], windowSize[1]);

	ImGui::Image(
		(void*)(size_t)Orbital::Renderer::GetFrame(), windowSize, ImVec2(0, 1), ImVec2(1, 0)
	);


	ImGui::End();
	ImGui::GetStyle().WindowPadding = ImVec2(12, 12);
}