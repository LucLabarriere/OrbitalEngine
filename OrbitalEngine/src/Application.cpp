#include "OrbitalEngine/Events.h"
#include "OrbitalEngine/Graphics.h"
#include "OrbitalEngine/Logic.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"

#define OE_DISPATCH_EVENT(eventType)\
dispatcher.Dispatch< ## eventType ## Event>([this]( ## eventType ## Event e) -> bool {\
	return On##eventType(e);\
});

namespace Orbital
{
	Application::Application()
	{
		#if defined(ORBITAL_DEBUG)
			Logger::SetLevel(Logger::Level::Trace);
		#endif
	
		Settings::Initialize();

		mWindow = Scope<Window>(Window::Create(
			Settings::Get(Settings::UIntSetting::WindowWidth),
			Settings::Get(Settings::UIntSetting::WindowHeight),
			"Orbital"
		));

		mWindow->SetApplicationCallBack(std::bind(&Application::OnEvent, this, std::placeholders::_1));

		Inputs::Initialize(mWindow);
		TextureManager::Initialize();
		ShaderManager::Initialize();
		Renderer::Initialize();
		MaterialManager::Initialize();
		MeshManager::Initialize();
		Renderer::InitializeBatchManager();
		Renderer::InitializeFramebuffers();
		Metrics::Initialize();

		mActiveScene = &mScene;
		Entity::SetSceneReference(&mActiveScene);
		mScene.Initialize();
	}

	Application::~Application()
	{
		Logger::Info("Application: Terminating");
		mWindow.reset();
		Renderer::Terminate();
		MeshManager::Terminate();
		TextureManager::Terminate();
		ShaderManager::Terminate();
		MaterialManager::Terminate();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);

		OE_DISPATCH_EVENT(KeyPressed);
		OE_DISPATCH_EVENT(MouseButtonPressed);
		OE_DISPATCH_EVENT(MouseScrolled);
	}

	void Application::Run()
	{
		OnLoad();

		Time dt;

		while (!mWindow->ShouldClose())
		{
			dt = Time() - mTimeAtLastUpdate;
			mTimeAtLastUpdate = Time();

			Metrics::OnUpdate(dt);

			bool vsyncEnabled = Metrics::Get<bool>(Metric::VSyncEnabled);
			if (vsyncEnabled != mWindow->IsVSyncEnabled())
			{
				mWindow->SetVSyncEnabled(vsyncEnabled);
			}

			OnUpdate(dt);
		}

		Logger::Trace("Leaving Application");
	}
}
