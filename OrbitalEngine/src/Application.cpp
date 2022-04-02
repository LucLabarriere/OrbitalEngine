#include "OrbitalEngine/Events.h"
#include "OrbitalEngine/Utils.h"
#include "OrbitalEngine/Logic.h"
#include "OrbitalEngine/Graphics.h"
#include "OrbitalEngine/Components.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"


namespace Orbital
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
		}
		Logger::Trace("Leaving Application");
	}


}
