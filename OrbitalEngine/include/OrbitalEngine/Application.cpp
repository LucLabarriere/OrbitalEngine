#include "OrbitalEngine/Application.h"
#include "OrbitalEngine/Shader.h"
#include "OrbitalEngine/Vertices.h"
#include "VertexBuffer.h"

namespace OrbitalEngine
{

	Application::Application()
	{
		#if defined(ORBITAL_DEBUG)
		spdlog::set_level(spdlog::level::trace);
		#endif

		m_window = Scope<Window>(Window::Create(800, 600, "Application"));
	}

	Application::~Application()
	{
		glfwTerminate();
	}

	void Application::run()
	{
		Ref<Shader> shader = Scope<Shader>(Shader::Create(
			0,
			"Base",
			"c:/Users/lucla/Work/Programmes/Orbital/OrbitalEngine/assets/shaders/Base.glsl"
		));

		float positions[9] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		unsigned int vao;
		glad_glGenVertexArrays(1, &vao);
		glad_glBindVertexArray(vao);
		Ref<VertexBuffer> buffer(VertexBuffer::Create(OE_STATIC_DRAW));

		Vertex<Position3, Color4> vert1 = { { -0.5f, -0.5f, 0.0f}, {0.0f, 0.9f, 0.1f, 1.0f} };
		Vertex<Position3, Color4> vert2 = { {  0.5f, -0.5f, 0.0f}, {0.0f, 0.9f, 0.1f, 1.0f} };
		Vertex<Position3, Color4> vert3 = { { -0.5f,  0.5f, 0.0f}, {0.0f, 0.9f, 0.1f, 1.0f} };
		VertexContainer<Position3, Color4> vertices(
			vert1, vert2, vert3
		);

		buffer->bind();
		vertices.allocateMemory(*buffer);
		vertices.setLayout(*buffer);

		while (!m_window->shouldClose())
		{
			glad_glClearColor(0.1f, 0.0f, 0.0f, 1.0f);
			glad_glClear(GL_COLOR_BUFFER_BIT);
			shader->bind();
			glad_glBindVertexArray(vao);
			glad_glDrawArrays(GL_TRIANGLES, 0, 3);
			m_window->onUpdate();
		}

		OE_DEBUG("Application: Terminating");

		glad_glDeleteVertexArrays(1, &vao);
		buffer.reset();
		m_window.reset();
	}
}
