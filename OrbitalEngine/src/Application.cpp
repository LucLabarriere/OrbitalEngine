#include "OrbitalEngine/Events.h"
#include "OrbitalEngine/Utils.h"
#include "OrbitalEngine/Logic.h"
#include "OrbitalEngine/Graphics.h"
#include "OrbitalEngine/Components.h"
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
	
		Settings::Initialize();

		m_window = Scope<Window>(Window::Create(
			Settings::Get(Settings::UIntSetting::WindowWidth),
			Settings::Get(Settings::UIntSetting::WindowHeight),
			"Application"
		));

		m_window->setApplicationCallBack(std::bind(&Application::onEvent, this, std::placeholders::_1));
		m_layerStack = CreateScope<LayerStack>();

		MeshManager::Initialize();
		BatchManager::Initialize();
		ShaderManager::Initialize();
		Renderer::Initialize();
		TextureManager::Initialize();
		Inputs::Initialize(m_window);

		m_camera = CreateRef<Camera>();
		m_cameraController = CreateScope<CameraController>(m_camera);
	}

	Application::~Application()
	{
		Logger::Info("Application: Terminating");
		m_window.reset();
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
		Renderer::Terminate();
		TextureManager::Terminate();
		ShaderManager::Terminate();
	}

	void Application::onEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<KeyPressedEvent>([this](KeyPressedEvent& e) -> bool {
			m_cameraController->onKeyPressed(e); // TODO Move into Editor

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
			m_cameraController->onMouseScrolled(e); // TODO Move into Editor

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

		entt::registry registry;

		unsigned int size_x = 5;
		unsigned int size_y = 5;
		for (unsigned int i = 0; i <= size_x; i++)
		{
			for (unsigned int j = 0; j <= size_y; j++)
			{
				auto entity = registry.create();

				Components::Transform t = {
					{ -1.0f, -1.0f, 0.0f },
					{  0.0f,  0.0f, 0.0f },
					{  0.2f,  0.2f, 0.2f }
				};

				float positionX = (float)i / size_x * 2;
				float positionY = (float)j / size_y * 2;
				float rotation = (float)j / size_x * 2 * 180.0f;

				t.Position += glm::vec3(positionX, positionY, 0.0f);
				t.Rotation = glm::vec3(rotation, rotation, rotation);

				registry.emplace<Components::Transform>(entity, t);
				registry.emplace<Components::MeshRenderer>(entity, MeshManager::Get("Cube"), false, true);
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

			m_cameraController->onUpdate(dt);

			TextureManager::Bind("Damier");
			const auto& shader = ShaderManager::GetShader("Base");
			shader->bind();
			shader->setUniform1i("u_TexId", 0);
			shader->setUniformMat4f("u_VPMatrix", m_camera->getVPMatrix());

			for (auto& layer: *m_layerStack)
			{
				layer.get()->update(dt);
			}

			auto view = registry.view<Components::Transform, Components::MeshRenderer>();
			for (auto entity : view)
			{
				auto& transform = view.get<Components::Transform>(entity);
				auto& meshRenderer = view.get<Components::MeshRenderer>(entity);
				transform.Rotation += 10.0f * dt.seconds();
				
				BatchManager::RegisterMesh(meshRenderer, transform);
			}

			BatchManager::RenderBatches();
			Renderer::Get()->displayFrame();

			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			m_window->onUpdate();
		}
		Logger::Trace("Leaving Application");
	}


}
