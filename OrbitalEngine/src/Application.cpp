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
	} \
	return x(e)

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
		Metrics::Initialize();
	}

	Application::~Application()
	{
		Logger::Info("Application: Terminating");
		m_window.reset();
		Renderer::Terminate();
		TextureManager::Terminate();
		ShaderManager::Terminate();
	}

	void Application::onEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<KeyPressedEvent>([this](KeyPressedEvent& e) -> bool {
			OE_DISPATCH_LAYER(onKeyPressed);
		});

		dispatcher.dispatch<KeyReleasedEvent>([this](KeyReleasedEvent& e) -> bool {
			OE_DISPATCH_LAYER(onKeyReleased);
		});

		dispatcher.dispatch<MouseMovedEvent>([this](MouseMovedEvent& e) -> bool {
			OE_DISPATCH_LAYER(onMouseMoved);
		});

		dispatcher.dispatch<MouseScrolledEvent>([this](MouseScrolledEvent& e) -> bool {
			OE_DISPATCH_LAYER(onMouseScrolled);
		});

		dispatcher.dispatch<MouseButtonPressedEvent>([this](MouseButtonPressedEvent& e) -> bool {
			OE_DISPATCH_LAYER(onMouseButtonPressed);
		});

		dispatcher.dispatch<MouseButtonReleasedEvent>([this](MouseButtonReleasedEvent& e) -> bool {
			OE_DISPATCH_LAYER(onMouseButtonReleased);
		});

		dispatcher.dispatch<WindowResizedEvent>([this](WindowResizedEvent& e) -> bool {
			OE_DISPATCH_LAYER(onWindowResized);
		});
	}

	void Application::run()
	{
		onStart();

		Time dt;
		while (!m_window->shouldClose())
		{
			dt = Time() - m_timeAtLastUpdate;
			m_timeAtLastUpdate = Time();

			Metrics::OnUpdate(dt);
			onUpdate(dt);

			for (auto& layer : *m_layerStack)
			{
				layer.get()->update(dt);
			}

		}
		Logger::Trace("Leaving Application");
	}


}
