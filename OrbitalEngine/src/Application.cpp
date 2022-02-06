#include "OrbitalEngine/Application.h"
#include "OrbitalEngine/Shader.h"
#include "OrbitalEngine/Vertices.h"
#include "OrbitalEngine/Logger.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include <ranges>

#define OE_DISPATCH_LAYER(x) \
	for (auto& layer : *m_layerStack) \
	{ \
		if (layer.get()->x(e)) \
			return true; \
	}

namespace OrbitalEngine
{
	Application::Application()
	{
		#if defined(ORBITAL_DEBUG)
			Logger::SetLevel(Logger::Level::Debug);
		#endif
	
		m_window = Scope<Window>(Window::Create(800, 600, "Application"));
		m_window->setApplicationCallBack(std::bind(&Application::onEvent, this, std::placeholders::_1));
		m_layerStack = CreateScope<LayerStack>();
	}

	Application::~Application()
	{
		Logger::Info("Application: Terminating");
		glfwTerminate();
	}

	void Application::onEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<KeyPressedEvent>([this](KeyPressedEvent& e) -> bool {
			OE_DISPATCH_LAYER(onKeyPressed)
			return false;
		});

		dispatcher.dispatch<KeyReleasedEvent>([this](KeyReleasedEvent& e) -> bool {
			OE_DISPATCH_LAYER(onKeyReleased)
			return false;
		});

		dispatcher.dispatch<MouseMovedEvent>([this](MouseMovedEvent& e) -> bool {
			OE_DISPATCH_LAYER(onMouseMoved)
			return false;
		});

		dispatcher.dispatch<MouseScrolledEvent>([this](MouseScrolledEvent& e) -> bool {
			OE_DISPATCH_LAYER(onMouseScrolled)
			return false;
		});

		dispatcher.dispatch<MouseButtonPressedEvent>([this](MouseButtonPressedEvent& e) -> bool {
			OE_DISPATCH_LAYER(onMouseButtonPressed)
			return false;
		});

		dispatcher.dispatch<MouseButtonReleasedEvent>([this](MouseButtonReleasedEvent& e) -> bool {
			OE_DISPATCH_LAYER(onMouseButtonReleased)
			return false;
		});
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

		Time timeAtLastUpdate;
		Time dt;

		while (!m_window->shouldClose())
		{
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			ImGui::Text("Hello, world %d", 123);
			ImGui::Render();

			glad_glClearColor(0.1f, 0.0f, 0.0f, 1.0f);
			glad_glClear(GL_COLOR_BUFFER_BIT);

			dt = Time() - timeAtLastUpdate;
			timeAtLastUpdate = Time();
			for (auto& layer: *m_layerStack)
			{
				layer.get()->update(dt);
			}

			shader->bind();
			vao->bind();
			glad_glDrawArrays(GL_TRIANGLES, 0, 3);


			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			m_window->onUpdate();
		}

		vao.reset();
		vbo.reset();
		m_window.reset();
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}


}
