#include "AssetManagerPanel.h"
#include "OrbitalEngine/Graphics/TextureManager.h"
#include "OrbitalEngine/Graphics/ShaderManager.h"
#include "Inspector.h"

AssetManagerPanel::AssetManagerPanel()
{

}

void AssetManagerPanel::render()
{
	if (ImGui::Begin("Assets"))
	{
		if (ImGui::Button("Reload shaders"))
		{
			ShaderManager::ReloadShaders();
		}
		ImGui::BeginChild("Assets", ImVec2(0, 0), true);

		int i = 0;

		ImGuiSelectableFlags selectableFlags = ImGuiSelectableFlags_SpanAllColumns;
		for (auto& texture : *TextureManager::GetInstance())
		{
			std::string text = std::format("Texture: {}", texture->getTag());

			if (ImGui::Selectable(text.c_str(), m_selected == i, selectableFlags))
			{
				m_selected = i;
				Inspector::SetTexture(texture);
			}
			i += 1;
		}

		for (auto& shader : *ShaderManager::GetInstance())
		{
			std::string text = std::format("Shader: {}", shader->getTag());

			if (ImGui::Selectable(text.c_str(), m_selected == i, selectableFlags))
			{
				m_selected = i;
				Inspector::SetText(shader->getContent());
			}
			i += 1;
		}

		for (auto& material : *MaterialManager::GetInstance())
		{
			std::string text = std::format("Material: {}", material->getTag());

			if (ImGui::Selectable(text.c_str(), m_selected == i, selectableFlags))
			{
				m_selected = i;
				Inspector::SetMaterial(material);
			}
			i += 1;
		}

		ImGui::EndChild();
	}
	ImGui::End();
}
