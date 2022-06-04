#pragma once

#include "OrbitalEngine/Utils.h"
#include "imgui.h"

class Editor
{
public:
	static void OnUpdate()
	{
		if (Orbital::Inputs::IsMouseEnabled())
		{
			ImGui::GetIO().ConfigFlags &= ~ImGuiConfigFlags_NoMouse;
		}
		else
		{
			ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NoMouse;
		}
	}
};
