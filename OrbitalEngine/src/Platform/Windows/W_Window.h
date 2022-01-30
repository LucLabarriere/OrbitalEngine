#pragma once

#include "OrbitalEngine/Window.h"

namespace OrbitalEngine
{
	class ORBITAL_API W_Window : public Window
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
		int m_majorVersion = 4;
		int m_minorVersion = 6;
		GLFWwindow* m_glfwWindow = nullptr;
	};
}