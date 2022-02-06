#pragma once

#include "OrbitalEngine/Window.h"
#include "OrbitalEngine/Time.h"
#include "OrbitalEngine/LayerStack.h"

namespace OrbitalEngine
{
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
	};	
}