#pragma once

#include "OrbitalEngine/Events.h"

namespace OrbitalEngine
{
	class Window;

	class Inputs
	{
	public:
		static void Initialize(Scope<Window>& window);
		static void Terminate() { delete s_instance;  }
		static bool IsKeyPressed(int keyCode) { return s_instance->isKeyPressed(keyCode); };

	protected:
		Inputs() { };

	private:
		virtual bool isKeyPressed(int keyCode) const = 0;

	private:
		inline static Inputs* s_instance = nullptr;
	};
}