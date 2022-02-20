#pragma once

#include "OrbitalEngine/Utils.h"
#include "OrbitalEngine/Logic/Window.h"
#include "OrbitalEngine/Logic/LayerStack.h"

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