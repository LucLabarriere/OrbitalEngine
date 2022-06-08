#include "EditorApplication.h"
#include "OrbitalEngine/Graphics.h"
#include "OrbitalEngine/Logic.h"
#include "OrbitalEngine/Components.h"
#include "Editor.h"
#include "Clipboard.h"
#include "Tools.h"



EditorApplication::EditorApplication() : Application()
{

}

EditorApplication::~EditorApplication()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	Tools::Terminate();
}

void EditorApplication::OnLoad()
{
	mCurrentSceneTag = "Sandbox";
	mSceneManager.NewScene(mCurrentSceneTag);

	// TODO: move most of the things into a start up script tied to the Scene entity.
	// - Add a freeCamera entity with transform and camera components
	// - It should be possible to hide it from the editor
	// - Remove position from camera, add reference to transform instead
	Tools::Initialize();
	
	mEditorCamera = OE::ActiveScene->CreateEntity("FreeCamera", OE_LAST_LAYER);
	mEditorCamera.AddComponent<Camera>();
	mEditorCamera.AddComponent<FreeCameraController>();
	auto& freeCameraController = mEditorCamera.GetComponent<NativeScriptManager>().Push<FreeCameraController>();
	freeCameraController->SetPosition({ 1.5f, 1.5f, 1.5f });
	freeCameraController->Rotate({ -30.0f, 130.f });

	OE::ActiveScene->SetMainCamera(mEditorCamera);

	mMainCamera = OE::ActiveScene->CreateEntity("Player");
	mMainCamera.AddComponent<Camera>();
	auto& playerController = mMainCamera.GetComponent<NativeScriptManager>().Push<FirstPersonController>();
	playerController->SetPosition({ 0.0f, 0.5f, -1.0f });

	auto floor = OE::ActiveScene->CreateEntity("Floor");
	auto& tFloor = floor.AddComponent<Transform>(Transform({
		{ 0.0f,  0.0f, 0.0f },
		{ 90.0f, 0.0f, 0.0f },
		{ 10.0f, 10.0f, 1.0f }
	}));

	floor.AddComponent<MeshRenderer>("Quad", &tFloor, true, "Blank");

	auto cube = OE::ActiveScene->CreateEntity("Cube");
	auto& tCube = cube.AddComponent<Transform>(Transform({
		{ 0.0f, 0.5f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
		{ 1.0f, 1.0f, 1.0f }
	}));

	auto& mr = cube.AddComponent<MeshRenderer>("Cube", &tCube, true, "Damier");

	auto pointLight = OE::ActiveScene->CreateEntity("Point Light");
	auto& tPointLight = pointLight.AddComponent<Transform>(Transform({
		{ 0.0f, 0.5f, 1.3f },
		{ 0.0f, 0.0f, 0.0f },
		{ 0.1f, 0.1f, 0.1f }
	}));

	auto& lPointLight = pointLight.AddComponent<PointLight>();
	lPointLight.Position = &tPointLight.GetPosition();
	lPointLight.Diffuse = { 0.0f, 0.0f, 1.0f };
	lPointLight.Specular = { 0.0f, 0.0f, 1.0f };
	pointLight.AddComponent<MeshRenderer>("Cube", &tPointLight);

	auto pointLight2 = OE::ActiveScene->CreateEntity("Point Light2");
	auto& tPointLight2 = pointLight2.AddComponent<Transform>(Transform({
		{ 1.3f, 0.5f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
		{ 0.1f, 0.1f, 0.1f }
	}));

	auto& lPointLight2 = pointLight2.AddComponent<PointLight>();
	lPointLight2.Position = &tPointLight2.GetPosition();
	lPointLight2.Diffuse = { 1.0f, 0.0f, 0.0f };
	lPointLight2.Specular = { 1.0f, 0.0f, 0.0f };
	pointLight2.AddComponent<MeshRenderer>("Cube", &tPointLight2);

	auto sun = OE::ActiveScene->CreateEntity("Sun");
	sun.AddComponent<DirectionalLight>();

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

	mViewport = CreateRef<Viewport>(this);
	mHierarchyPanel = CreateRef<HierarchyPanel>();
	mHierarchyPanel->Initialize();
	mMetricsPanel = CreateScope<MetricsPanel>(&freeCameraController);
	mBatchesPanel = CreateScope<BatchesPanel>();
	mAssetManagerPanel = CreateScope<AssetManagerPanel>();
	mFileExplorerPanel = CreateScope<FileExplorerPanel>();

	Inspector::Initialize();
	Clipboard::Initialize();

	//mSceneManager.SerializeActiveScene("scenes/Sandbox.oes");
	//mSceneManager.DeserializeScene("scenes/Sandbox.oes");

	Stop(); // The scene is stopped on startup
}

void EditorApplication::OnUpdate(Time dt)
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	Editor::OnUpdate();
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None | ImGuiDockNodeFlags_PassthruCentralNode;
	ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
	ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
	
	mViewport->Render();
	mHierarchyPanel->Update();
	mHierarchyPanel->Render();
	mMetricsPanel->Render();
	mBatchesPanel->Render();
	mAssetManagerPanel->Render();
	mFileExplorerPanel->Render();

	//NativeScriptManager::OnUpdate(dt);
	Inspector::Render();

	if (mMetricsPanel->IsDemoShown())
		ImGui::ShowDemoWindow();

	ImGui::Render();

	Renderer::Get()->NewFrame();
	OE::ActiveScene->OnUpdate(dt);
	OE::ActiveScene->Begin();
	OE::ActiveScene->Render();

	Renderer::RenderBatches();
	Renderer::RenderUnits();

	Renderer::Get()->DisplayFrame();

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	OE::ActiveScene->End();

	mWindow->OnUpdate();
}


void EditorApplication::Play()
{
	// TODO: make cameras work here
	mState = EditorState::Playing;
	mEditorCamera.GetComponent<NativeScriptManager>().Get<FreeCameraController>()->SetUpdating(false);
	mRuntimeSceneManager = mSceneManager.Copy();
	mRuntimeSceneManager.SetActive(mCurrentSceneTag);
	OE::ActiveScene->SetUpdating(true);
	OE::ActiveScene->SetMainCamera(mMainCamera);
	mSceneManager.OnStart();
}

void EditorApplication::Stop()
{
	mState = EditorState::Stopped;
	mSceneManager.SetActive(mCurrentSceneTag);
	mSceneManager.OnExit();
	OE::ActiveScene->SetUpdating(false);
	mEditorCamera.GetComponent<NativeScriptManager>().Get<FreeCameraController>()->SetUpdating(true);
	OE::ActiveScene->SetMainCamera(mEditorCamera);
	//mSceneManager.SerializeActiveScene("scenes/Sandbox.oes");
}

bool EditorApplication::OnMouseScrolled(MouseScrolledEvent& e)
{
	return false;
}

bool EditorApplication::OnKeyPressed(KeyPressedEvent& e)
{
	if (mState == EditorState::Stopped)
	{
		if (e.GetKeyCode() == OE_KEY_C && Inputs::IsKeyDown(OE_KEY_LEFT_CONTROL))
		{
			Clipboard::Copy(Inspector::GetInspectedObject());
		}

		else if (e.GetKeyCode() == OE_KEY_V && Inputs::IsKeyDown(OE_KEY_LEFT_CONTROL))
		{
			Clipboard::Paste();
		}
	}
	else
	{
		if (e.GetKeyCode() == OE_KEY_ESCAPE)
		{
			Stop();
		}
	}

	return false;
}
