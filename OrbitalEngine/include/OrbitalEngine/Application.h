#pragma once

#include "OrbitalEngine/Window.h"

namespace OrbitalEngine
{
	class Application
	{
	public:
		Application();
		~Application();
			
		void run();

	private:
		Scope<Window> m_window;
	};	
}