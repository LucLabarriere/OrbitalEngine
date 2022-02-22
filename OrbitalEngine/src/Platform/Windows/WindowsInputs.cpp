#include "WindowsInputs.h"
#include "OrbitalEngine/Events.h"
#include "OrbitalEngine/Logic/Application.h"

namespace OrbitalEngine
{
	void Inputs::Initialize(Scope<Window>& window)
	{
		s_instance = new WindowsInputs(static_cast<GLFWwindow*>(window->getNativeWindow()));
	}

	WindowsInputs::WindowsInputs(GLFWwindow* glfwWindow)
		: Inputs(), m_glfwWindow(glfwWindow)
	{
	}

	bool WindowsInputs::isKeyPressed(int keyCode) const
	{
		if (OE_EVENT_PRESS == glfwGetKey(m_glfwWindow, keyCode)
			|| OE_EVENT_REPEAT == glfwGetKey(m_glfwWindow, keyCode))
			return true;
	}
}