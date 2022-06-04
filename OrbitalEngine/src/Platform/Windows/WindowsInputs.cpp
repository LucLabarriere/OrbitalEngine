#include "WindowsInputs.h"
#include "OrbitalEngine/Events.h"
#include "OrbitalEngine/Logic/Application.h"

namespace Orbital
{
	void Inputs::Initialize(Scope<Window>& window)
	{
		s_instance = new WindowsInputs(static_cast<GLFWwindow*>(window->getNativeWindow()));
	}

	WindowsInputs::WindowsInputs(GLFWwindow* glfwWindow)
		: Inputs(), m_glfwWindow(glfwWindow)
	{
	}

	bool WindowsInputs::isKeyDown(int keyCode) const
	{
		if (OE_EVENT_PRESS == glfwGetKey(m_glfwWindow, keyCode)
			|| OE_EVENT_REPEAT == glfwGetKey(m_glfwWindow, keyCode))
			return true;
		return false;
	}

	bool WindowsInputs::isMouseButtonDown(int buttonCode) const
	{
		if (OE_EVENT_PRESS == glfwGetMouseButton(m_glfwWindow, buttonCode))
			return true;
		return false;
	}

	void WindowsInputs::lockCursor(bool value)
	{
		if (value)
			glfwSetInputMode(m_glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		else
			glfwSetInputMode(m_glfwWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	const glm::vec2 WindowsInputs::getMousePosition() const
	{
		double xPos;
		double yPos;
		glfwGetCursorPos(m_glfwWindow, &xPos, &yPos);
		return glm::vec2(xPos, yPos);
	}
}