#include "OpenGLWindow.h"
#include "OrbitalEngine/Logic/Application.h"
#include "backends/imgui_impl_glfw.h"

namespace Orbital
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
			case GL_DEBUG_SEVERITY_HIGH:         Logger::Error("OpenGL: id:{}, type:{} \n-> {}", id, type, message); return;
			case GL_DEBUG_SEVERITY_MEDIUM:       Logger::Error("OpenGL: id:{}, type:{} \n-> {}", id, type, message); return;
			case GL_DEBUG_SEVERITY_LOW:          Logger::Warn("OpenGL: id:{}, type:{} \n-> {}", id, type, message); return;
			case GL_DEBUG_SEVERITY_NOTIFICATION: Logger::Debug("OpenGL: id:{}, type:{} \n-> {}", id, type, message); return;
		}
	}

	void _post_call_callback(const char* name, void* funcptr, int len_args, ...) {
		GLenum error_code;
		error_code = glad_glGetError();

		if (error_code != GL_NO_ERROR)
		{
			Logger::Error("GLAD: ERROR {} in {}\n", error_code, name);
		}
	}

	void _pre_call_callback(const char* name, void* funcptr, int len_args, ...) {
		GLenum error_code;
		error_code = glad_glGetError();

		if (error_code != GL_NO_ERROR)
		{
			Logger::Error("GLAD: ERROR {} in {}\n", error_code, name);
		}
	}

	Window* Window::Create(unsigned int width, unsigned int height, const std::string& title)
	{
		return new OpenGLWindow(width, height, title);
	}

	void error_callback(int error, const char* description)
	{
		Logger::Error("GLFW: {}, {}", error, description);
	}

	void info_callback(int info, const char* description)
	{
		Logger::Info("GLFW: {}, {}", info, description);
	}

	OpenGLWindow::OpenGLWindow(unsigned int width, unsigned int height, const std::string& title)
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
		bool gladSuccess = gladLoadGL(glfwGetProcAddress);
		OE_ASSERT(gladSuccess, "W_Window: Could not initialize GLAD (OpenGL Error)");
		Logger::Info("W_Window: OpenGL {} context created.", (const char*)glad_glGetString(GL_VERSION));

		glad_glEnable(GL_DEBUG_OUTPUT);
		glad_glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glad_glDebugMessageCallback(OpenGLMessageCallback, nullptr);
		glad_glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
		gladSetGLPreCallback((GLADprecallback)_pre_call_callback);
		gladSetGLPostCallback((GLADpostcallback)_post_call_callback);
		glfwSwapInterval(1);

		ImGui_ImplGlfw_InitForOpenGL(m_glfwWindow, true);
		ImGui_ImplOpenGL3_Init("#version 430");

		mInitialized = true;
	}

	OpenGLWindow::~OpenGLWindow()
	{
		Shutdown();
	}

	bool OpenGLWindow::ShouldClose()
	{
		return glfwWindowShouldClose(m_glfwWindow);
	}

	void OpenGLWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_glfwWindow);
	}

	void OpenGLWindow::Shutdown()
	{
		Logger::Info("W_Window: shutting down");
		glfwDestroyWindow(m_glfwWindow);
		mInitialized = false;
	}

	void OpenGLWindow::EnableCursor()
	{
		glfwSetInputMode(m_glfwWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		glfwSetInputMode(m_glfwWindow, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
	}

	void OpenGLWindow::DisableCursor()
	{
		glfwSetInputMode(m_glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwSetInputMode(m_glfwWindow, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
	}

	void* OpenGLWindow::GetNativeWindow() const
	{
		return m_glfwWindow;
	}

	GLFWwindow* OpenGLWindow::createWindow()
	{
		glfwSetErrorCallback(error_callback);
		m_glfwWindow = glfwCreateWindow(mWidth, mHeight, mTitle.c_str(), NULL, NULL);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwSetWindowUserPointer(m_glfwWindow, this);

		glfwSetWindowSizeCallback(
			m_glfwWindow,
			[](GLFWwindow* window, int width, int height) {
				auto& self = *static_cast<OpenGLWindow*>(glfwGetWindowUserPointer(window));
				self.mWidth = (unsigned int)width;
				self.mHeight = (unsigned int)height;
				Settings::Get(Settings::UIntSetting::WindowWidth) = self.mWidth;
				Settings::Get(Settings::UIntSetting::WindowHeight) = self.mHeight;

				WindowResizedEvent e(self.mWidth, self.mHeight);
				self.ApplicationCallback(e);
			}
		);

		glfwSetKeyCallback(
			m_glfwWindow,
			[](GLFWwindow* window, int key, int scanCode, int action, int mods) {
				auto& self = *static_cast<OpenGLWindow*>(glfwGetWindowUserPointer(window));

				switch (action)
				{
					case GLFW_PRESS || GLFW_REPEAT:
					{
						KeyPressedEvent e(key);
						self.ApplicationCallback(e);
						break;
					}
					case GLFW_RELEASE:
					{
						KeyReleasedEvent e(key);
						self.ApplicationCallback(e);
						break;
					}
				}
			}
		);

		glfwSetCursorPosCallback(
			m_glfwWindow,
			[](GLFWwindow* window, double xPos, double yPos) {
				auto& self = *static_cast<OpenGLWindow*>(glfwGetWindowUserPointer(window));
				MouseMovedEvent e(static_cast<float>(xPos), static_cast<float>(yPos));
				self.ApplicationCallback(e);
			}
		);

		glfwSetMouseButtonCallback(
			m_glfwWindow,
			[](GLFWwindow* window, int button, int action, int mods) {
				auto& self = *static_cast<OpenGLWindow*>(glfwGetWindowUserPointer(window));
				double xPos, yPos;
				glfwGetCursorPos(window, &xPos, &yPos);

				switch (action)
				{
					case GLFW_PRESS:
					{
						MouseButtonPressedEvent e(static_cast<float>(xPos), static_cast<float>(yPos), button);
						self.ApplicationCallback(e);
						break;
					}

					case GLFW_RELEASE:
					{
						MouseButtonReleasedEvent e(static_cast<float>(xPos), static_cast<float>(yPos), button);
						self.ApplicationCallback(e);
						break;
					}
				}
			});

		glfwSetScrollCallback(
			m_glfwWindow,
			[](GLFWwindow* window, double xOffset, double yOffset) {
				auto& self = *static_cast<OpenGLWindow*>(glfwGetWindowUserPointer(window));
				double xPos, yPos;
				glfwGetCursorPos(window, &xPos, &yPos);
				MouseScrolledEvent e(
					static_cast<float>(xPos), static_cast<float>(yPos),
					static_cast<float>(xOffset), static_cast<float>(yOffset)
				);
				self.ApplicationCallback(e);
			});

		return m_glfwWindow;
	}
}
