#pragma once

#include "OrbitalEngine/Utils.h"

using namespace Orbital;

class BatchesPanel
{
public:
	BatchesPanel() { }

	void render()
	{
		// TODO: Upon changin the Mesh, call DeleteMesh() then RegisterMesh()
		// Remake the whole Components system:
		// class Component
		// mush have:
		// virtual void destroy() = 0

		if (ImGui::Begin("Batches"))
		{
			auto bm = Renderer::GetBatchManager().lock();
			const auto& batches = bm->getBatches();
			std::vector<const char*> batchNames;

			for (auto& batchEntry : *bm)
			{
				batchNames.push_back(batchEntry.first.c_str());
			}


			ImGuiTabBarFlags tabFlags = ImGuiTabBarFlags_None;
			if (ImGui::BeginTabBar("Batches tab", tabFlags))
			{
				for (auto& batchEntry : *bm)
				{
					if (ImGui::BeginTabItem(batchEntry.first.c_str()))
					{
						const auto& vertices = batchEntry.second->getVertices();
						const auto& freeVertices = batchEntry.second->getFreeVerticesList();

						for (size_t i = 0; i < vertices.getCount(); i++)
						{
							std::string text = std::to_string(i);
							if (!freeVertices[i])
							{
								text += fmt::format(": p[{: .2e} {: .2e} {: .2e}], c[{: .2e} {: .2e} {: .2e}, {: .2e}], n[{: .2e} {: .2e} {: .2e}], t[{: .1e} {: .1e}]",
									vertices[i].position[0], vertices[i].position[1], vertices[i].position[2],
									vertices[i].color[0], vertices[i].color[1], vertices[i].color[2], vertices[i].color[3],
									vertices[i].normal[0], vertices[i].normal[1], vertices[i].normal[2],
									vertices[i].texCoords[0], vertices[i].texCoords[1]
								);
							}
							ImGui::Text(text.c_str());
						}
						ImGui::EndTabItem();
					}
				}
				ImGui::EndTabBar();
			}

			//ImGui::ListBox("listbox", &m_currentItem, batchNames.data(), 2);

			/*for (auto& batchEntry : *bm)
			{
				ImGui::Text(batchEntry.first.c_str());
			}*/
		}
		ImGui::End();
	}

private:
	int m_currentItem = 1;
};