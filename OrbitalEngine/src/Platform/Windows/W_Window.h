#pragma once

#include "OrbitalEngine/Logic/Window.h"

namespace OrbitalEngine
{
	class W_Window : public Window
	{
	public:
		W_Window(unsigned int width, unsigned int height, const std::string& title);
		virtual ~W_Window() override;
		
		virtual bool shouldClose() override;
		virtual void onUpdate() override;
		virtual void shutdown() override;

	private:
		GLFWwindow* createWindow();

	private:
		GLFWwindow* m_glfwWindow = nullptr;
	};
}