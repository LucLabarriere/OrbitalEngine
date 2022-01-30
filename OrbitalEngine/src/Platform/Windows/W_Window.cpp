#include "W_Window.h"

namespace OrbitalEngine
{
	void OpenGLMessageCallback(
		unsigned source,
		unsigned type,
		unsigned id,
		unsigned severity,
		int length,
		const char* message,
		const void* userParam)
	{
		switch (severity)
		{
			case GL_DEBUG_SEVERITY_HIGH:         OE_ERROR("OpenGL: {}, {}, {}", id, type, message); return;
			case GL_DEBUG_SEVERITY_MEDIUM:       OE_WARNING("OpenGL: {}, {}, {}", id, type, message); return;
			case GL_DEBUG_SEVERITY_LOW:          OE_INFO("OpenGL: {}, {}, {}", id, type, message); return;
			case GL_DEBUG_SEVERITY_NOTIFICATION: OE_INFO("OpenGL: {}, {}, {}", id, type, message); return;
		}
	}
	Window* Window::Create(unsigned int width, unsigned int height, const std::string& title)
	{
		return new W_Window(width, height, title);
	}

	void error_callback(int error, const char* description)
	{
		OE_ERROR("GLFW Error: {0}, {1}", error, description);
	}

	void info_callback(int info, const char* description)
	{
		OE_INFO("GLFW Info: {0}, {1}", info, description);
	}

	W_Window::W_Window(unsigned int width, unsigned int height, const std::string& title)
		: Window(width, height, title)
	{
		OE_INFO("W_Window: Creating the window");

		int glfwSuccess = glfwInit();
		OE_ASSERT(glfwSuccess, "W_Window: Could not initialize GLFW");

		glfwSetErrorCallback(error_callback);

		m_glfwWindow = createWindow();

		glfwMakeContextCurrent(m_glfwWindow);
		bool gladSuccess = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		OE_ASSERT(gladSuccess, "W_Window: Could not initialize GLAD (OpenGL Error)");
		OE_INFO("OpenGL {0} context created.", glad_glGetString(GL_VERSION));

		glad_glDebugMessageCallback(OpenGLMessageCallback, nullptr);
		glad_glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
		glad_glEnable(GL_DEBUG_OUTPUT);
		glad_glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

		glfwSwapInterval(1);

		m_initialized = true;
	}

	W_Window::~W_Window()
	{
		shutdown();
	}

	bool W_Window::shouldClose()
	{
		return glfwWindowShouldClose(m_glfwWindow);
	}

	void W_Window::onUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_glfwWindow);
	}

	void W_Window::shutdown()
	{
		OE_INFO("W_Window: shutting down");
		glfwDestroyWindow(m_glfwWindow);
		m_initialized = false;
	}
	GLFWwindow* W_Window::createWindow()
	{
		glfwSetErrorCallback(info_callback);
		m_minorVersion++;

		while (!m_glfwWindow)
		{
			m_minorVersion--;

			if (m_minorVersion < 0 && m_majorVersion == 4)
			{
				m_majorVersion = 3;
				m_minorVersion = 3;
			}
			else if(m_minorVersion < 0 && m_majorVersion == 3)
			{
				OE_RAISE_SIGSEGV("Error, you need at least version 3.0");
			}

			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, m_majorVersion);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, m_minorVersion);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			m_glfwWindow = glfwCreateWindow(m_width, m_height, m_title.c_str(), NULL, NULL);
		}
		glfwSetErrorCallback(error_callback);

		return m_glfwWindow;
	}
}
