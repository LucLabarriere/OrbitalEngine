#pragma once

#include "OrbitalEngine/Utils.h"
#include "OrbitalEngine/Graphics/Window.h"
#include "OrbitalEngine/Logic/LayerStack.h"
#include "OrbitalEngine/Graphics/CameraController.h"

namespace OrbitalEngine
{
	class Camera;

	class Application
	{
	public:
		Application();
		virtual ~Application();
		
		void onEvent(Event& e);
		void run();
		

	protected:
		Scope<Window> m_window;
		Scope<LayerStack> m_layerStack;
		Ref<Camera> m_camera;
		Scope<CameraController> m_cameraController;
	};	
}