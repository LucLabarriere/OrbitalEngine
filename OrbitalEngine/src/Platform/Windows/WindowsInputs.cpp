#include "WindowsInputs.h"
#include "OrbitalEngine/Events.h"
#include "OrbitalEngine/Logic/Application.h"

namespace Orbital
{
	void Inputs::Initialize(Scope<Window>& window)
	{
		sInstance = new WindowsInputs(static_cast<GLFWwindow*>(window->GetNativeWindow()));
	}

	WindowsInputs::WindowsInputs(GLFWwindow* glfwWindow)
		: Inputs(), mGlfwWindow(glfwWindow)
	{
	}

	bool WindowsInputs::IsKeyDownImpl(int keyCode) const
	{
		if (OE_EVENT_PRESS == glfwGetKey(mGlfwWindow, keyCode)
			|| OE_EVENT_REPEAT == glfwGetKey(mGlfwWindow, keyCode))
			return true;
		return false;
	}

	bool WindowsInputs::IsMouseButtonDownImpl(int buttonCode) const
	{
		if (OE_EVENT_PRESS == glfwGetMouseButton(mGlfwWindow, buttonCode))
			return true;
		return false;
	}

	void WindowsInputs::LockCursorImpl(bool value)
	{
		if (value)
			glfwSetInputMode(mGlfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		else
			glfwSetInputMode(mGlfwWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	const glm::vec2 WindowsInputs::GetMousePositionImpl() const
	{
		double xPos;
		double yPos;
		glfwGetCursorPos(mGlfwWindow, &xPos, &yPos);
		return glm::vec2(xPos, yPos);
	}
}