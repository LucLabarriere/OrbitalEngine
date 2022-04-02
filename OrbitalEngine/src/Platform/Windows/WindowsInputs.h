#pragma once

#include "OrbitalEngine/Utils.h"

namespace Orbital
{
	class WindowsInputs: public Inputs
	{
	private:
		WindowsInputs(GLFWwindow* glfwWindow);
		virtual bool isKeyDown(int keyCode) const override;
		virtual bool isMouseButtonDown(int buttonCode) const override;
		virtual const glm::vec2 getMousePosition() const override;
	
	private:
		friend Inputs;
		GLFWwindow* m_glfwWindow = nullptr;
	};
}