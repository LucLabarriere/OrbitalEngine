#pragma once

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "imgui.h"
#include "OrbitalEngine/Graphics/Renderer.h"
#include "OrbitalEngine/Logic/Application.h"
#include "Widgets.h"

using namespace Orbital;

// TODO move this out from this file
OE_SCRIPT_INFO(FreeCameraController)
OE_SCRIPT_INFO(FirstPersonController)

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

	virtual void OnLoad() override;
	virtual void OnStart() override { };
	virtual void OnUpdate(Time dt) override;

	void Play();
	void Stop();
	bool IsPlaying() const { return mState == EditorState::Playing ? true : false; }

	virtual bool OnMouseScrolled(MouseScrolledEvent& e) override;
	virtual bool OnKeyPressed(KeyPressedEvent& e) override;

	void CheckRenderAreaSize(unsigned int width, unsigned int height)
	{
		if (width != mRenderAreaWidth || height != mRenderAreaHeight)
		{
			mRenderAreaWidth = width;
			mRenderAreaHeight = height;
			Settings::Get(Settings::UIntSetting::RenderingAreaWidth) = width;
			Settings::Get(Settings::UIntSetting::RenderingAreaHeight) = height;
			Settings::Get(Settings::FloatSetting::AspectRatio) = (float)width / height;
			OE::ActiveScene->SetAspectRatio(Settings::Get(Settings::FloatSetting::AspectRatio));
			Renderer::OnWindowResized();
		}
	}

private:
	EditorState mState = EditorState::Stopped;
	unsigned int mRenderAreaWidth = 0;
	unsigned int mRenderAreaHeight = 0;
	Ref<Viewport> mViewport;
	Ref<HierarchyPanel> mHierarchyPanel;
	Entity mEditorCamera;
	Entity mMainCamera;

	SceneManager mRuntimeSceneManager;
	std::string mCurrentSceneTag;

	Scope<MetricsPanel> mMetricsPanel;
	Scope<BatchesPanel> mBatchesPanel;
	Scope<AssetManagerPanel> mAssetManagerPanel;
	Scope<FileExplorerPanel> mFileExplorerPanel;
};