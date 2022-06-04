#pragma once

#include "OrbitalEngine/Graphics/Window.h"

namespace Orbital
{
	class OpenGLWindow : public Window
	{
	public:
		OpenGLWindow(unsigned int width, unsigned int height, const std::string& title);
		virtual ~OpenGLWindow() override;
		
		virtual bool shouldClose() override;
		virtual void onUpdate() override;
		virtual void shutdown() override;
		virtual void enableCursor() override;
		virtual void disableCursor() override;

		virtual void* getNativeWindow() const override;
		
		virtual void setVSyncEnabled(bool value)
		{
			m_vsyncEnabled = value;
			glfwSwapInterval((int)value);
		}

	private:
		GLFWwindow* createWindow();

	private:
		GLFWwindow* m_glfwWindow = nullptr;
	};
}