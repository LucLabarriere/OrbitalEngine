#pragma once

#include "OrbitalEngine/Graphics/Renderer.h"
#include "OrbitalEngine/Utils/Misc.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "imgui.h"

class EditorApplication;

class Viewport
{
public:
	Viewport(EditorApplication* app);
	void render();

private:
	EditorApplication* m_app;
};