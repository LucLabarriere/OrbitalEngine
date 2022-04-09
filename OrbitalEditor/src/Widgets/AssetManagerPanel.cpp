#include "AssetManagerPanel.h"
#include "OrbitalEngine/Graphics/TextureManager.h"
#include "OrbitalEngine/Graphics/ShaderManager.h"
#include "Inspector.h"

AssetManagerPanel::AssetManagerPanel()
{

}

void AssetManagerPanel::render()
{
	ImGui::Begin("Assets");

	ImGui::BeginChild("Files", ImVec2(0, 0), true);

	int i = 0;

	ImGuiSelectableFlags selectableFlags = ImGuiSelectableFlags_SpanAllColumns;
	for (auto& texture : *TextureManager::GetInstance())
	{
		if (ImGui::Selectable(texture->getName().c_str(), m_selected == i, selectableFlags))
		{
			m_selected = i;
			Inspector::SetTexture(texture);
		}
		i += 1;
	}

	for (auto& shader : *ShaderManager::GetInstance())
	{
		if (ImGui::Selectable(shader->getName().c_str(), m_selected == i, selectableFlags))
		{
			m_selected = i;
			Inspector::SetText(shader->getContent());
		}
		i += 1;
	}



	ImGui::EndChild();

	ImGui::End();
}
