#pragma once

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "imgui.h"
#include "entt/entt.hpp"
#include "OrbitalEngine/Graphics/Renderer.h"
#include "OrbitalEngine/Logic/Application.h"
#include "Widgets.h"

using namespace Orbital;

class EditorApplication : public Application
{
public:
	EditorApplication();
	virtual ~EditorApplication() override;

	virtual void onStart() override;
	virtual void onUpdate(Time dt) override;

	virtual bool onMouseScrolled(MouseScrolledEvent& e) override;

	void checkRenderAreaSize(unsigned int width, unsigned int height)
	{
		if (width != m_renderAreaWidth || height != m_renderAreaHeight)
		{
			m_renderAreaWidth = width;
			m_renderAreaHeight = height;
			Settings::Get(Settings::UIntSetting::RenderingAreaWidth) = width;
			Settings::Get(Settings::UIntSetting::RenderingAreaHeight) = height;
			Settings::Get(Settings::FloatSetting::AspectRatio) = (float)width / height;
			m_scene->getCamera()->setAspectRatio(Settings::Get(Settings::FloatSetting::AspectRatio));
			Renderer::OnWindowResized();
		}
	}

private:
	Ref<Scene> m_scene;
	Scope<CameraController> m_cameraController;

	unsigned int m_renderAreaWidth;
	unsigned int m_renderAreaHeight;
	Ref<HierarchyPanel> m_hierarchyPanel;
	Scope<MetricsPanel> m_metricsPanel;
	Scope<AssetManagerPanel> m_assetManagerPanel;
	Scope<FileExplorerPanel> m_fileExplorerPanel;

	Vec3 m_direction = { 0.1f, -1.0f, 0.1f };
	Vec3 m_position2 = { 0.1f, -1.0f, 0.1f };
	Vec3 m_ambient2 = { 0.2f, 0.2f, 0.2f };
	Vec3 m_diffuse2 = { 1.0f, 1.0f, 1.0f };
	Vec3 m_specular2 = { 1.0f, 1.0f, 1.0f };
	float m_constant2 = 1.0f;
	float m_linear2 = 0.1f;
	float m_quadratic2 = 2.0f;
	float m_cutOff = 0.3f;
	float m_edge = 0.01f;
};