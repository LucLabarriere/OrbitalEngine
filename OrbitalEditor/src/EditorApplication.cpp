#include "EditorApplication.h"
#include "OrbitalEngine/Components.h"
#include "OrbitalEngine/Graphics.h"
#include "OrbitalEngine/Logic.h"
#include "Widgets.h"

EditorApplication::EditorApplication() : Application()
{
	m_scene = CreateRef<Scene>();
	m_scene->initialize();
	m_cameraController = CreateScope<CameraController>(m_scene->getCamera());

	m_layerStack->push(CreateRef<GuiLayer>());
}


EditorApplication::~EditorApplication()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void EditorApplication::onStart()
{
	unsigned int size_x = 5;
	unsigned int size_y = 5;
	for (unsigned int i = 0; i <= size_x; i++)
	{
		for (unsigned int j = 0; j <= size_y; j++)
		{
			//std::cout << fmt::vformat(msg,
				//fmt::make_format_args(std::forward<Args>(args)...));
			
			Components::Tag tag(fmt::format("Cube_{}_{}", i, j).c_str());
			auto entity = m_scene->createEntity(tag);

			Components::Transform t = {
				{ -1.0f, -1.0f, 2.0f },
				{  0.0f,  0.0f, 0.0f },
				{  0.2f,  0.2f, 0.2f }
			};

			float positionX = (float)i / size_x * 2;
			float positionY = (float)j / size_y * 2;
			float rotation = (float)j / size_x * 2 * 180.0f;

			t.Position += Vec3(positionX, positionY, 0.0f);
			t.Rotation = Vec3(rotation, rotation, rotation);

			entity.add<Components::Transform>(t);
			entity.add<Components::MeshRenderer>(MeshManager::Get("Cube"), false, true);
		}
	}

	m_scene->getEntity("Cube_1_1").get<Components::Hierarchy>().setParent(m_scene->getEntity("Cube_2_1"));

	auto entity = m_scene->createEntity("Quad");

	Components::Transform t = {
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f },
		{ 0.2f, 0.2f, 0.2f }
	};

	entity.add<Components::Transform>(t);
	entity.add<Components::MeshRenderer>(MeshManager::Get("Quad"), false, true);

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
}

void EditorApplication::onUpdate(Time dt)
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None | ImGuiDockNodeFlags_PassthruCentralNode;
	ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
	ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");

	ImGui::GetStyle().WindowPadding = ImVec2(0, 0);
	ImGui::Begin("Scene Viewport");
	checkRenderAreaSize(ImGui::GetWindowSize()[0], ImGui::GetWindowSize()[1]);
	ImGui::Image(
		(void*)Renderer::GetFrame(), ImGui::GetWindowSize(), ImVec2(0, 1), ImVec2(1, 0)
	);
	ImGui::End();
	ImGui::GetStyle().WindowPadding = ImVec2(12, 12);

	ImGui::Begin("Debug informations");
	ImGui::Text("Time per frame %.2f ms",				Metrics::Get<Time>(Metric::TimePerFrame).milliseconds());
	ImGui::Text("FPS %.2f",								Metrics::Get<float>(Metric::FrameRate));
	ImGui::Text("Approximate time per frame %.2f ms",	Metrics::Get<Time>(Metric::ApproximateTimePerFrame).milliseconds());
	ImGui::Text("Approximate FPS %.2f",					Metrics::Get<float>(Metric::ApproximateFrameRate));
	ImGui::Checkbox("Show demo window", &m_isDemoShown);
	ImGui::End();

	HierarchyPanel hierarchyPanel(m_scene);
	hierarchyPanel.render();

	if (m_isDemoShown)
		ImGui::ShowDemoWindow();

	ImGui::Render();

	Renderer::Get()->newFrame();

	m_cameraController->onUpdate(dt);

	TextureManager::Bind("Damier");
	const auto& shader = ShaderManager::GetShader("Base");
	shader->bind();
	shader->setUniform1i("u_TexId", 0);
	shader->setUniformMat4f("u_VPMatrix", m_scene->getCamera()->getVPMatrix());

	auto view = m_scene->getRegistry()->view<Components::Transform, Components::MeshRenderer>();
	for (auto entity : view)
	{
		auto& transform = view.get<Components::Transform>(entity);
		auto& meshRenderer = view.get<Components::MeshRenderer>(entity);

		if (meshRenderer.Mesh->getTag() == "Cube")
			transform.Rotation += 10.0f * dt.seconds();
		
		BatchManager::RegisterMesh(meshRenderer, transform);
	}

	BatchManager::RenderBatches();

	Renderer::Get()->displayFrame();

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	m_window->onUpdate();
}

bool EditorApplication::onMouseScrolled(MouseScrolledEvent& e)
{
	m_cameraController->onMouseScrolled(e);
	return false;
}