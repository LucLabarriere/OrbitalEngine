#include "W_Window.h"
#include "OrbitalEngine/Application.h"
#include "OrbitalEngine/Logger.h"
#include "backends/imgui_impl_glfw.h"

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
			case GL_DEBUG_SEVERITY_HIGH:         Logger::Error("OpenGL: id:{}, type:{} -> {}", id, type, message); return;
			case GL_DEBUG_SEVERITY_MEDIUM:       Logger::Error("OpenGL: id:{}, type:{} -> {}", id, type, message); return;
			case GL_DEBUG_SEVERITY_LOW:          Logger::Warn("OpenGL: id:{}, type:{} -> {}", id, type, message); return;
			case GL_DEBUG_SEVERITY_NOTIFICATION: Logger::Debug("OpenGL: id:{}, type:{} -> {}", id, type, message); return;
		}
	}

	Window* Window::Create(unsigned int width, unsigned int height, const std::string& title)
	{
		return new W_Window(width, height, title);
	}

	void error_callback(int error, const char* description)
	{
		Logger::Error("GLFW: {}, {}", error, description);
	}

	void info_callback(int info, const char* description)
	{
		Logger::Info("GLFW: {}, {}", info, description);
	}

	W_Window::W_Window(unsigned int width, unsigned int height, const std::string& title)
		: Window(width, height, title)
	{
		auto context = ImGui::CreateContext();
		ImGui::SetCurrentContext(context);

		Logger::Info("W_Window: Creating the window");

		int glfwSuccess = glfwInit();
		OE_ASSERT(glfwSuccess, "W_Window: Could not initialize GLFW");

		glfwSetErrorCallback(error_callback);

		m_glfwWindow = createWindow();

		glfwMakeContextCurrent(m_glfwWindow);
		bool gladSuccess = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		OE_ASSERT(gladSuccess, "W_Window: Could not initialize GLAD (OpenGL Error)");
		Logger::Info("W_Window: OpenGL {} context created.", (const char*)glad_glGetString(GL_VERSION));

		glad_glEnable(GL_DEBUG_OUTPUT);
		glad_glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glad_glDebugMessageCallback(OpenGLMessageCallback, nullptr);
		glad_glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);

		glfwSwapInterval(0);

		ImGui_ImplGlfw_InitForOpenGL(m_glfwWindow, true);
		ImGui_ImplOpenGL3_Init("#version 430");

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
		Logger::Info("W_Window: shutting down");
		glfwDestroyWindow(m_glfwWindow);
		m_initialized = false;
	}

	GLFWwindow* W_Window::createWindow()
	{
		glfwSetErrorCallback(error_callback);
		m_glfwWindow = glfwCreateWindow(m_width, m_height, m_title.c_str(), NULL, NULL);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwSetWindowUserPointer(m_glfwWindow, this);

		glfwSetKeyCallback(
			m_glfwWindow,
			[](GLFWwindow* window, int key, int scanCode, int action, int mods) {
				auto& self = *static_cast<W_Window*>(glfwGetWindowUserPointer(window));

				switch (action)
				{
					case GLFW_PRESS || GLFW_REPEAT:
					{
						KeyPressedEvent e(key);
						self.applicationCallback(e);
						break;
					}
					case GLFW_RELEASE:
					{
						KeyReleasedEvent e(key);
						self.applicationCallback(e);
						break;
					}
				}
			}
		);

		glfwSetCursorPosCallback(
			m_glfwWindow,
			[](GLFWwindow* window, double xPos, double yPos) {
				auto& self = *static_cast<W_Window*>(glfwGetWindowUserPointer(window));
				MouseMovedEvent e(static_cast<float>(xPos), static_cast<float>(yPos));
				self.applicationCallback(e);
			}
		);

		glfwSetScrollCallback(
			m_glfwWindow,
			[](GLFWwindow* window, double xOffset, double yOffset) {
				auto& self = *static_cast<W_Window*>(glfwGetWindowUserPointer(window));
				double xPos, yPos;
				glfwGetCursorPos(window, &xPos, &yPos);
				MouseScrolledEvent e(
					static_cast<float>(xPos), static_cast<float>(yPos),
					static_cast<float>(xOffset), static_cast<float>(yOffset)
				);
				self.applicationCallback(e);
			});

		return m_glfwWindow;
	}
}
