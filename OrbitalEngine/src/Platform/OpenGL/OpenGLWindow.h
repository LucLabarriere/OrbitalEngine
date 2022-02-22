#pragma once

#include "OrbitalEngine/Graphics/Window.h"

namespace OrbitalEngine
{
	class OpenGLWindow : public Window
	{
	public:
		OpenGLWindow(unsigned int width, unsigned int height, const std::string& title);
		virtual ~OpenGLWindow() override;
		
		virtual bool shouldClose() override;
		virtual void onUpdate() override;
		virtual void shutdown() override;

		virtual void* getNativeWindow() const override;

	private:
		GLFWwindow* createWindow();

	private:
		GLFWwindow* m_glfwWindow = nullptr;
	};
}