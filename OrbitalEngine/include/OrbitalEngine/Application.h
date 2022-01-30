#pragma once

#include "OrbitalEngine/Window.h"

namespace OrbitalEngine
{
	class ORBITAL_API Application
	{
	public:
		Application();
		~Application();
			
		void run();

	private:
		Scope<Window> m_window;
	};	
}