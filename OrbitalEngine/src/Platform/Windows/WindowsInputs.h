#pragma once

#include "OrbitalEngine/Utils.h"

namespace Orbital
{
	class WindowsInputs: public Inputs
	{
	private:
		WindowsInputs(GLFWwindow* glfwWindow);
		virtual bool IsKeyDownImpl(int keyCode) const override;
		virtual bool IsMouseButtonDownImpl(int buttonCode) const override;
		virtual void LockCursorImpl(bool value) override;
		virtual const glm::vec2 GetMousePositionImpl() const override;
		virtual bool IsMouseEnabledImpl() const override
		{
			return glfwGetInputMode(mGlfwWindow, GLFW_CURSOR)
				== GLFW_CURSOR_DISABLED ? false : true;
		}
	
	private:
		friend Inputs;
		GLFWwindow* mGlfwWindow = nullptr;
	};
}