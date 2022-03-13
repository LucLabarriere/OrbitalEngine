#pragma once

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "imgui.h"
#include "entt/entt.hpp"

#include "GuiLayer.h"
#include "OrbitalEngine/Graphics/Renderer.h"

using namespace OrbitalEngine;

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
		if (width != m_renderAreaWidth && height != m_renderAreaHeight)
		{
			m_renderAreaWidth = width;
			m_renderAreaHeight = height;
			Settings::Get(Settings::UIntSetting::RenderingAreaWidth) = width;
			Settings::Get(Settings::UIntSetting::RenderingAreaHeight) = height;
			Settings::Get(Settings::FloatSetting::AspectRatio) = (float)width / height;
			Renderer::OnWindowResized();
			m_camera->setAspectRatio(Settings::Get(Settings::FloatSetting::AspectRatio));
		}
	}

private:
	Ref<Camera> m_camera;
	Scope<CameraController> m_cameraController;
	entt::registry m_registry;

	unsigned int m_renderAreaWidth;
	unsigned int m_renderAreaHeight;
	bool m_isDemoShown = true;
};