#include "EditorApplication.h"
#include "OrbitalEngine/Graphics.h"
#include "OrbitalEngine/Logic.h"
#include "OrbitalEngine/Components.h"
#include "Editor.h"
#include "Clipboard.h"
#include "Tools.h"

EditorApplication::EditorApplication() : Application()
{
	//m_cameraController = CreateRef<CameraController>(&m_camera);
}

EditorApplication::~EditorApplication()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	Tools::Terminate();
}

void EditorApplication::onLoad()
{
	// TODO: move most of the things into a start up script tied to the Scene entity.
	// - Add a freeCamera entity with transform and camera components
	// - It should be possible to hide it from the editor
	// - Remove position from camera, add reference to transform instead
	Tools::Initialize();
	Widget::SetActiveScene(&m_activeScene);

	m_editorCamera = m_activeScene->CreateEntity("FreeCamera", OE_LAST_LAYER);
	m_editorCamera.AddComponent<Camera>();
	auto& freeCameraController = m_editorCamera.AddComponent<FreeCameraController>();
	m_activeScene->SetMainCamera(m_editorCamera);

	m_mainCamera = m_activeScene->CreateEntity("Player");
	m_mainCamera.AddComponent<Camera>();
	auto& playerController = m_mainCamera.AddComponent<FirstPersonController>();
	playerController.setPosition({ 0.0f, 0.5f, -1.0f });

	auto floor = m_activeScene->CreateEntity("Floor");
	auto& tFloor = floor.AddComponent<Transform>(Transform({
		{ 0.0f,  0.0f, 0.0f },
		{ 90.0f, 0.0f, 0.0f },
		{ 10.0f, 10.0f, 1.0f }
	}));

	floor.AddComponent<MeshRenderer>("Quad", &tFloor, true, "Blank");

	auto cube = m_activeScene->CreateEntity("Cube");
	auto& tCube = cube.AddComponent<Transform>(Transform({
		{ 0.0f, 0.5f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
		{ 1.0f, 1.0f, 1.0f }
	}));

	auto& mr = cube.AddComponent<MeshRenderer>("Cube", &tCube, true, "Damier");

	auto pointLight = m_activeScene->CreateEntity("Point Light");
	auto& tPointLight = pointLight.AddComponent<Transform>(Transform({
		{ 0.0f, 0.5f, 1.3f },
		{ 0.0f, 0.0f, 0.0f },
		{ 0.1f, 0.1f, 0.1f }
	}));

	auto& lPointLight = pointLight.AddComponent<PointLight>();
	lPointLight.Position = &tPointLight.Position();
	lPointLight.Diffuse = { 0.0f, 0.0f, 1.0f };
	lPointLight.Specular = { 0.0f, 0.0f, 1.0f };
	pointLight.AddComponent<MeshRenderer>("Cube", &tPointLight);

	auto pointLight2 = m_activeScene->CreateEntity("Point Light2");
	auto& tPointLight2 = pointLight2.AddComponent<Transform>(Transform({
		{ 1.3f, 0.5f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
		{ 0.1f, 0.1f, 0.1f }
	}));

	auto& lPointLight2 = pointLight2.AddComponent<PointLight>();
	lPointLight2.Position = &tPointLight2.Position();
	lPointLight2.Diffuse = { 1.0f, 0.0f, 0.0f };
	lPointLight2.Specular = { 1.0f, 0.0f, 0.0f };
	pointLight2.AddComponent<MeshRenderer>("Cube", &tPointLight2);

	auto sun = m_activeScene->CreateEntity("Sun");
	sun.AddComponent<DirectionalLight>();

	freeCameraController.setPosition({ 1.5f, 1.5f, 1.5f });
	freeCameraController.rotate({ -30.0f, 130.f });

	ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	ImGui::GetIO().Fonts->AddFontFromFileTTF(Settings::GetAssetPath("fonts/NotoSans-Regular.ttf").c_str(), 32);
	ImGui::GetIO().Fonts->Build();

	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
	window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	window_flags |= ImGuiWindowFlags_NoBackground;

	ImGuiStyle mainStyle = ImGui::GetStyle();

	mainStyle.WindowPadding = ImVec2(12, 12);
	mainStyle.WindowRounding = 5.0f;
	mainStyle.FramePadding = ImVec2(5, 5);
	mainStyle.FrameRounding = 4.0f;
	mainStyle.ItemSpacing = ImVec2(12, 8);
	mainStyle.ItemInnerSpacing = ImVec2(8, 6);
	mainStyle.IndentSpacing = 25.0f;
	mainStyle.ScrollbarSize = 15.0f;
	mainStyle.ScrollbarRounding = 9.0f;
	mainStyle.GrabMinSize = 5.0f;
	mainStyle.GrabRounding = 3.0f;

	ImGui::GetStyle() = mainStyle;

	ImGui::GetIO().FontGlobalScale = 0.55;

	m_viewport = CreateRef<Viewport>(this);
	m_hierarchyPanel = CreateRef<HierarchyPanel>();
	m_hierarchyPanel->initialize();
	m_metricsPanel = CreateScope<MetricsPanel>(&freeCameraController);
	m_batchesPanel = CreateScope<BatchesPanel>();
	m_assetManagerPanel = CreateScope<AssetManagerPanel>();
	m_fileExplorerPanel = CreateScope<FileExplorerPanel>();
	Inspector::Initialize();
	Clipboard::Initialize();

	stop(); // The scene is stopped on startup
}

void EditorApplication::onUpdate(Time dt)
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	Editor::OnUpdate();
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None | ImGuiDockNodeFlags_PassthruCentralNode;
	ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
	ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
	
	m_viewport->render();
	m_hierarchyPanel->update();
	m_hierarchyPanel->render();
	m_metricsPanel->render();
	m_batchesPanel->render();
	m_assetManagerPanel->render();
	m_fileExplorerPanel->render();

	//NativeScriptManager::OnUpdate(dt);
	Inspector::Render();

	if (m_metricsPanel->isDemoShown())
		ImGui::ShowDemoWindow();

	ImGui::Render();

	Renderer::Get()->newFrame();
	m_activeScene->OnUpdate(dt);
	m_activeScene->Begin();
	m_activeScene->Render();

	Renderer::RenderBatches();
	Renderer::RenderUnits();

	Renderer::Get()->displayFrame();

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	m_activeScene->End();
	m_window->onUpdate();
}


void EditorApplication::play()
{
	// TODO: make cameras work here
	m_state = EditorState::Playing;
	m_editorCamera.GetComponent<FreeCameraController>().setUpdating(false);
	m_activeScene = &m_runtimeScene;
	m_runtimeScene = Scene();
	m_runtimeScene = m_scene.Copy(m_runtimeScene);
	m_activeScene->SetUpdating(true);
	m_activeScene->SetMainCamera(m_mainCamera);
	m_activeScene->OnStart();
}

void EditorApplication::stop()
{
	m_state = EditorState::Stopped;
	m_activeScene->OnExit();
	m_activeScene = &m_scene;
	m_activeScene->SetUpdating(false);
	m_editorCamera.GetComponent<FreeCameraController>().setUpdating(true);
	m_activeScene->SetMainCamera(m_editorCamera);
}

bool EditorApplication::onMouseScrolled(MouseScrolledEvent& e)
{
	return false;
}

bool EditorApplication::onKeyPressed(KeyPressedEvent& e)
{
	if (m_state == EditorState::Stopped)
	{
		if (e.getKeyCode() == OE_KEY_C && Inputs::IsKeyDown(OE_KEY_LEFT_CONTROL))
		{
			Clipboard::Copy(Inspector::GetInspectedObject());
		}

		else if (e.getKeyCode() == OE_KEY_V && Inputs::IsKeyDown(OE_KEY_LEFT_CONTROL))
		{
			Clipboard::Paste();
		}
	}
	else
	{
		if (e.getKeyCode() == OE_KEY_ESCAPE)
		{
			stop();
		}
	}

	return false;
}
