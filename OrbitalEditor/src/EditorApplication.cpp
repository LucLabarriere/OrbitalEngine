#include "EditorApplication.h"
#include "OrbitalEngine/Components.h"
#include "OrbitalEngine/Graphics.h"
#include "OrbitalEngine/Logic.h"
#include "Clipboard.h"
#include "Scripts/PlayerController.h"
#include "Tools.h"

EditorApplication::EditorApplication() : Application()
{
	m_cameraController = CreateRef<CameraController>(m_scene->getCamera());
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
	Tools::Initialize();
	auto floor = m_scene->createEntity("Floor");
	auto& tFloor = floor.add<Components::Transform>(Components::Transform({
		{ 0.0f,  0.0f, 0.0f },
		{ 90.0f, 0.0f, 0.0f },
		{ 10.0f, 10.0f, 1.0f }
	}));

	floor.add<Components::MeshRenderer>("Quad", &tFloor, true, "Blank");

	auto cube = m_scene->createEntity("Cube");
	auto& tCube = cube.add<Components::Transform>(Components::Transform({
		{ 0.0f, 0.5f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
		{ 1.0f, 1.0f, 1.0f }
	}));
	//cube.addScript<PlayerController>();
	cube.add<Components::NativeScript<PlayerController>>(
		NativeScriptManager::Create<PlayerController>(cube)
	);

	auto& mr = cube.add<Components::MeshRenderer>("Cube", &tCube, true, "Damier");

	auto pointLight = m_scene->createEntity("Point Light");
	auto& tPointLight = pointLight.add<Components::Transform>(Components::Transform({
		{ 0.0f, 0.5f, 1.3f },
		{ 0.0f, 0.0f, 0.0f },
		{ 0.1f, 0.1f, 0.1f }
	}));

	auto& lPointLight = pointLight.add<Components::PointLight>();
	lPointLight.Position = &tPointLight.Position();
	lPointLight.Diffuse = { 0.0f, 0.0f, 1.0f };
	lPointLight.Specular = { 0.0f, 0.0f, 1.0f };
	pointLight.add<Components::MeshRenderer>("Cube", &tPointLight);

	auto pointLight2 = m_scene->createEntity("Point Light2");
	auto& tPointLight2 = pointLight2.add<Components::Transform>(Components::Transform({
		{ 1.3f, 0.5f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
		{ 0.1f, 0.1f, 0.1f }
	}));

	auto& lPointLight2 = pointLight2.add<Components::PointLight>();
	lPointLight2.Position = &tPointLight2.Position();
	lPointLight2.Diffuse = { 1.0f, 0.0f, 0.0f };
	lPointLight2.Specular = { 1.0f, 0.0f, 0.0f };
	pointLight2.add<Components::MeshRenderer>("Cube", &tPointLight2);

	auto sun = m_scene->createEntity("Sun");
	sun.add<Components::DirectionalLight>();

	m_scene->getCamera()->setPosition({ 1.5f, 1.5f, 1.5f });
	m_scene->getCamera()->rotate({ -30.0f, 130.f });

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
	m_hierarchyPanel = CreateRef<HierarchyPanel>(m_scene);
	m_hierarchyPanel->initialize();
	m_metricsPanel = CreateScope<MetricsPanel>(m_cameraController);
	m_batchesPanel = CreateScope<BatchesPanel>();
	m_assetManagerPanel = CreateScope<AssetManagerPanel>();
	m_fileExplorerPanel = CreateScope<FileExplorerPanel>();
	Inspector::Initialize(m_scene);
	Clipboard::Initialize(m_scene);
}

void EditorApplication::onUpdate(Time dt)
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

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

	if (m_state == EditorState::Playing)
		NativeScriptManager::OnUpdate(dt);
	else
		m_cameraController->onUpdate(dt);

	Inspector::Render();

	if (m_metricsPanel->isDemoShown())
		ImGui::ShowDemoWindow();

	ImGui::Render();

	Renderer::Get()->newFrame();


	m_scene->beginScene();
	m_scene->render();

	Renderer::RenderBatches();
	Renderer::RenderUnits();

	Renderer::Get()->displayFrame();

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	m_scene->endScene();
	m_window->onUpdate();
}

bool EditorApplication::onMouseScrolled(MouseScrolledEvent& e)
{
	// TODO dispatch events to NativeScriptManager
	if (m_state != EditorState::Playing)
		m_cameraController->onMouseScrolled(e);

	return false;
}

bool EditorApplication::onKeyPressed(KeyPressedEvent& e)
{
	// TODO dispatch events to NativeScriptManager
	if (m_state != EditorState::Playing)
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

	return false;
}
