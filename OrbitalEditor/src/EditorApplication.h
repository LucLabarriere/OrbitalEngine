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
	//Ref<Camera> m_camera;
	//entt::registry m_registry;
	Ref<Scene> m_scene;
	Scope<CameraController> m_cameraController;

	unsigned int m_renderAreaWidth;
	unsigned int m_renderAreaHeight;
	bool m_isDemoShown = true;
};