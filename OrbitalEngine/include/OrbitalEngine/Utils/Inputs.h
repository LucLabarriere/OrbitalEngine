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
		static bool IsKeyDown(int keyCode) { return s_instance->isKeyDown(keyCode); };
		static bool IsMouseButtonDown(int buttonCode) { return s_instance->isMouseButtonDown(buttonCode); };
		static const glm::vec2 GetMousePosition() { return s_instance->getMousePosition(); }

	protected:
		Inputs() { };

	private:
		virtual bool isKeyDown(int keyCode) const = 0;
		virtual bool isMouseButtonDown(int buttonCode) const = 0;
		virtual const glm::vec2 getMousePosition() const = 0;

	private:
		inline static Inputs* s_instance = nullptr;
	};
}