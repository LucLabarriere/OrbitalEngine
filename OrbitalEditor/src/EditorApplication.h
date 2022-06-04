#pragma once

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "imgui.h"
#include "OrbitalEngine/Graphics/Renderer.h"
#include "OrbitalEngine/Logic/Application.h"
#include "Widgets.h"

using namespace Orbital;

class EditorApplication : public Application, public std::enable_shared_from_this<EditorApplication>
{
public:
	enum class EditorState
	{
		Playing = 0,
		Stopped
	};

public:
	EditorApplication();
	virtual ~EditorApplication() override;

	virtual void onLoad() override;
	virtual void onStart() override { };
	virtual void onUpdate(Time dt) override;

	void play();
	void stop();
	bool isPlaying() const { return m_state == EditorState::Playing ? true : false; }

	virtual bool onMouseScrolled(MouseScrolledEvent& e) override;
	virtual bool onKeyPressed(KeyPressedEvent& e) override;

	void checkRenderAreaSize(unsigned int width, unsigned int height)
	{
		if (width != m_renderAreaWidth || height != m_renderAreaHeight)
		{
			m_renderAreaWidth = width;
			m_renderAreaHeight = height;
			Settings::Get(Settings::UIntSetting::RenderingAreaWidth) = width;
			Settings::Get(Settings::UIntSetting::RenderingAreaHeight) = height;
			Settings::Get(Settings::FloatSetting::AspectRatio) = (float)width / height;
			m_activeScene->SetAspectRatio(Settings::Get(Settings::FloatSetting::AspectRatio));
			Renderer::OnWindowResized();
		}
	}

private:
	EditorState m_state = EditorState::Stopped;
	unsigned int m_renderAreaWidth = 0;
	unsigned int m_renderAreaHeight = 0;
	Ref<Viewport> m_viewport;
	Ref<HierarchyPanel> m_hierarchyPanel;
	Entity m_editorCamera;
	Entity m_mainCamera;
	Scene m_runtimeScene;

	Scope<MetricsPanel> m_metricsPanel;
	Scope<BatchesPanel> m_batchesPanel;
	Scope<AssetManagerPanel> m_assetManagerPanel;
	Scope<FileExplorerPanel> m_fileExplorerPanel;
};