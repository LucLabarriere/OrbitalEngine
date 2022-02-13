#include "OrbitalEngine/Application.h"
#include "OrbitalEngine/Shader.h"
#include "OrbitalEngine/Vertices.h"
#include "OrbitalEngine/IndexContainer.h"
#include "OrbitalEngine/Logger.h"
#include "OrbitalEngine/Components.h"
#include "OrbitalEngine/MeshManager.h"
#include "OrbitalEngine/Batch.h"
#include "OrbitalEngine/BatchManager.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"

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
			Logger::SetLevel(Logger::Level::Trace);
		#endif
	
		m_window = Scope<Window>(Window::Create(800, 600, "Application"));
		m_window->setApplicationCallBack(std::bind(&Application::onEvent, this, std::placeholders::_1));
		m_layerStack = CreateScope<LayerStack>();

		MeshManager::Initialize();
		BatchManager::Initialize();
	}

	Application::~Application()
	{
		Logger::Info("Application: Terminating");
		m_window.reset();
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
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

		entt::registry registry;

		auto entity1 = registry.create();
		Components::Transform t1 = {
			{ -0.5f, 0.5f, 0.0f },
			{  0.0f, 0.0f, 45.0f },
			{  0.5f, 0.5f, 1.0f }
		};
		registry.emplace<Components::Transform>(entity1, t1); // static batched
		registry.emplace<Components::MeshRenderer>(entity1, MeshManager::Get("Quad"), true, true);

		auto entity2 = registry.create();
		Components::Transform t2 = {
			{  0.5f, 0.5f, 0.0f },
			{  0.0f, 0.0f, 0.0f },
			{  0.5f, 0.5f, 1.0f }
		};
		registry.emplace<Components::Transform>(entity2, t2); // static !batched
		registry.emplace<Components::MeshRenderer>(entity2, MeshManager::Get("Quad"), true, false);

		auto entity3 = registry.create();
		Components::Transform t3 = {
			{ -0.5f,-0.5f, 0.0f },
			{  0.0f, 0.0f, 45.0f },
			{  0.5f, 0.5f, 1.0f }
		};
		registry.emplace<Components::Transform>(entity3, t3); // dynamic !batched
		registry.emplace<Components::MeshRenderer>(entity3, MeshManager::Get("Quad"), false, false);

		auto entity4 = registry.create();
		Components::Transform t4 = {
			{  0.5f,-0.5f, 0.0f },
			{  0.0f, 0.0f, 0.0f },
			{  0.5f, 0.5f, 1.0f }
		};
		registry.emplace<Components::Transform>(entity4, t4); // dynamic batched
		registry.emplace<Components::MeshRenderer>(entity4, MeshManager::Get("Quad"), false, true);

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

			auto view = registry.view<Components::Transform, Components::MeshRenderer>();
			for (auto entity : view)
			{
				auto& transform = view.get<Components::Transform>(entity);
				auto& meshRenderer = view.get<Components::MeshRenderer>(entity);
				
				BatchManager::RegisterMesh(meshRenderer, transform);

				if (meshRenderer.staticDraw and meshRenderer.batchedDraw)
					meshRenderer.Batch->requestFlush();
			}

			BatchManager::RenderBatches();

			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			m_window->onUpdate();
		}
	}


}
