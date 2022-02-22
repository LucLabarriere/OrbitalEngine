#include "OrbitalEngine/Application.h"
#include "OrbitalEngine/Shader.h"
#include "OrbitalEngine/Vertices.h"
#include "OrbitalEngine/IndexContainer.h"
#include "OrbitalEngine/Logger.h"
#include "OrbitalEngine/Components.h"
#include "OrbitalEngine/MeshManager.h"
#include "OrbitalEngine/Batch.h"
#include "OrbitalEngine/BatchManager.h"
#include "OrbitalEngine/Renderer.h"
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

		Renderer::Initialize();
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
		Renderer::Terminate();
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
			"/assets/shaders/Base.glsl"
		));

		entt::registry registry;

		unsigned int size_x = 30;
		unsigned int size_y = 30;
		for (unsigned int i = 0; i <= size_x; i++)
		{
			for (unsigned int j = 0; j <= size_y; j++)
			{
				auto entity = registry.create();

				Components::Transform t = {
					{ -1.0f ,-1.0f , 0.0f },
					{  0.0f , 0.0f , 0.0f },
					{  0.03f, 0.03f, 1.0f }
				};

				float positionX = (float)i / size_x * 2;
				float positionY = (float)j / size_y * 2;
				float rotation = (float)j / size_x * 2 * 180.0f;

				t.Position += glm::vec3(positionX, positionY, 0.0f);
				t.Rotation = glm::vec3(0.0f, 0.0f, rotation);

				registry.emplace<Components::Transform>(entity, t);
				registry.emplace<Components::MeshRenderer>(entity, MeshManager::Get("Quad"), true, false);
			}
		}

		Time timeAtLastUpdate;
		Time dt;

		std::vector<Time> times(100);
		size_t timeIndex = 0;
		float average = 0.0f;

		while (!m_window->shouldClose())
		{
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();


			ImGui::Text("Time per frame %f ms", dt.milliseconds());
			ImGui::Text("FPS %.2f", 1.0f / dt.seconds());
			ImGui::Text("Average FPS %.2f", 1.0f / average);
			ImGui::Render();

			Renderer::Get()->newFrame();

			dt = Time() - timeAtLastUpdate;
			timeAtLastUpdate = Time();

			times[timeIndex] = dt;
			timeIndex += 1;
			if (timeIndex == times.size())
				timeIndex = 0;

			average = 0;
			for (auto& t : times)
				average += t.seconds();
			average = average / times.size();


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
			}
			BatchManager::RenderBatches();

			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			m_window->onUpdate();
		}
	}


}
