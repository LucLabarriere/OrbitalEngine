#pragma once

#include "OrbitalEngine/Utils.h"

namespace OrbitalEngine
{
	class WindowsInputs: public Inputs
	{
	private:
		WindowsInputs(GLFWwindow* glfwWindow);
		virtual bool isKeyPressed(int keyCode) const override;
	
	private:
		friend Inputs;
		GLFWwindow* m_glfwWindow = nullptr;
	};
}