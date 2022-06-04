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
		virtual void lockCursor(bool value) override;
		virtual const glm::vec2 getMousePosition() const override;
		virtual bool isMouseEnabled() const override
		{
			return glfwGetInputMode(m_glfwWindow, GLFW_CURSOR)
				== GLFW_CURSOR_DISABLED ? false : true;
		}
	
	private:
		friend Inputs;
		GLFWwindow* m_glfwWindow = nullptr;
	};
}