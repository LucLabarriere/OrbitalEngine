#pragma once

#include "OrbitalEngine/Graphics/Window.h"

namespace Orbital
{
	class OpenGLWindow : public Window
	{
	public:
		OpenGLWindow(unsigned int width, unsigned int height, const std::string& title);
		virtual ~OpenGLWindow() override;
		
		virtual bool ShouldClose() override;
		virtual void OnUpdate() override;
		virtual void Shutdown() override;
		virtual void EnableCursor() override;
		virtual void DisableCursor() override;

		virtual void* GetNativeWindow() const override;
		
		virtual void SetVSyncEnabled(bool value)
		{
			mVsyncEnabled = value;
			glfwSwapInterval((int)value);
		}

	private:
		GLFWwindow* createWindow();

	private:
		GLFWwindow* m_glfwWindow = nullptr;
	};
}