#include "AssetManagerPanel.h"
#include "OrbitalEngine/Graphics/TextureManager.h"
#include "OrbitalEngine/Graphics/ShaderManager.h"
#include "Inspector.h"

AssetManagerPanel::AssetManagerPanel()
{

}

void AssetManagerPanel::Render()
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
			std::string text = std::format("Texture: {}", texture->GetTag());

			if (ImGui::Selectable(text.c_str(), mSelected == i, selectableFlags))
			{
				mSelected = i;
				Inspector::SetTexture(texture);
			}
			i += 1;
		}

		for (auto& shader : *ShaderManager::GetInstance())
		{
			std::string text = std::format("Shader: {}", shader->GetTag());

			if (ImGui::Selectable(text.c_str(), mSelected == i, selectableFlags))
			{
				mSelected = i;
				Inspector::SetText(shader->GetContent());
			}
			i += 1;
		}

		for (auto& material : *MaterialManager::GetInstance())
		{
			std::string text = std::format("Material: {}", material->GetTag());

			if (ImGui::Selectable(text.c_str(), mSelected == i, selectableFlags))
			{
				mSelected = i;
				Inspector::SetMaterial(material);
			}
			i += 1;
		}

		ImGui::EndChild();
	}
	ImGui::End();
}
