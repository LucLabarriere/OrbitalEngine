#include "OrbitalEngine/Application.h"
#include "OrbitalEngine/Shader.h"
#include "OrbitalEngine/Vertices.h"
#include "VertexBuffer.h"
#include "VertexArray.h"

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

		Ref<VertexArray> vao(VertexArray::Create());
		Ref<VertexBuffer> vbo(VertexBuffer::Create(OE_STATIC_DRAW));

		using V = Vertex<Position3, Color4>;

		VertexContainer<Position3, Color4> vertices(
			V({ -0.5f, -0.5f, 0.0f}, {0.1f, 0.9f, 0.1f, 1.0f}),
			V({  0.5f, -0.5f, 0.0f}, {0.9f, 0.1f, 0.1f, 1.0f}),
			V({ -0.5f,  0.5f, 0.0f}, {0.1f, 0.1f, 0.9f, 1.0f})
		);

		vao->bind();
		vbo->bind();
		vertices.allocateMemory(*vbo);
		vertices.setLayout(*vbo);

		while (!m_window->shouldClose())
		{
			glad_glClearColor(0.1f, 0.0f, 0.0f, 1.0f);
			glad_glClear(GL_COLOR_BUFFER_BIT);
			shader->bind();
			vao->bind();
			glad_glDrawArrays(GL_TRIANGLES, 0, 3);
			m_window->onUpdate();
		}

		OE_DEBUG("Application: Terminating");

		vao.reset();
		vbo.reset();
		m_window.reset();
	}
}
