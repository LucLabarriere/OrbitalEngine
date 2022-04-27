#include "FileExplorerPanel.h"
#include "OrbitalEngine/Graphics/TextureManager.h"

FileExplorerPanel::FileExplorerPanel()
{
	updateFiles();
}

void FileExplorerPanel::updateFiles()
{
	m_fileCount = std::distance(std::filesystem::directory_iterator(m_currentDirectory), std::filesystem::directory_iterator());
	m_fileNames.resize(m_fileCount);

	size_t i = 0;
	const auto& entries = std::filesystem::directory_iterator(m_currentDirectory);
	for (const auto& entry : entries)
	{
		m_fileNames[i] = entry.path().filename().string();
		i += 1;
	}

	m_selected = -1;
}

void FileExplorerPanel::changeFolder()
{
	std::filesystem::path newPath = m_currentDirectory / m_fileNames[m_selected];
	Logger::Trace("Path: {}", newPath.string());
	bool isDirectory = std::filesystem::is_directory(newPath);
	if (isDirectory)
	{
		m_currentDirectory = newPath;
	}
	updateFiles();
}

unsigned int FileExplorerPanel::getIconIndex(const std::string& fileName)
{
	std::filesystem::path filePath(std::filesystem::path(m_currentDirectory / fileName));
	std::string extension = filePath.extension().string();
	/*if (std::filesystem::is_directory(filePath))
		extension = "folder";*/
	
	if (extension == "folder")
		return 1;
	else if (extension == ".png" || extension == ".jpeg")
		return 2;
	else if (extension == ".txt")
		return 3;

	return 0;
}

void FileExplorerPanel::render()
{
	if (ImGui::Begin("Files"))
	{
		if (ImGui::Button("<"))
		{
			m_currentDirectory = m_currentDirectory.parent_path();
			updateFiles();
		}
		ImGui::Text(m_currentDirectory.parent_path().string().c_str());

		auto texture = TextureManager::Get("Icons").lock();
		ImGuiTableFlags tableFlags = ImGuiTableFlags_SizingFixedFit | 
			ImGuiTableFlags_ContextMenuInBody | ImGuiTableFlags_NoHostExtendX | ImGuiTableFlags_RowBg;
	
		ImGuiSelectableFlags selectableFlags = ImGuiSelectableFlags_SpanAllColumns | ImGuiSelectableFlags_AllowDoubleClick;

		if (ImGui::BeginTable("File explorer table", 2, tableFlags))
		{
			ImGui::TableSetupColumn("AAA", ImGuiTableColumnFlags_WidthFixed);
			ImGui::TableSetupColumn("BBB", ImGuiTableColumnFlags_WidthStretch);
			for (size_t i = 0; i < m_fileNames.size(); i++)
			{
				unsigned int iconIndex = getIconIndex(m_fileNames[i]);
				ImGui::TableNextRow();
				ImGui::TableNextColumn();
				ImGui::Image(
					(void*)(intptr_t)texture->getRendererId(),
					ImVec2(16, 16),
					ImVec2(0.2f * (float)iconIndex, 0),
					ImVec2(0.2f * ((float)iconIndex + 1), 1)
				);
				ImGui::TableNextColumn();

				bool selected = ImGui::Selectable(m_fileNames[i].c_str(), m_selected == i, selectableFlags);

				if (iconIndex == 2 && ImGui::BeginPopupContextItem(fmt::format("Load Texture {}", i).c_str()))
				{
					if (ImGui::Button("Load as Texture"))
						ImGui::OpenPopup(fmt::format("Load Texture Window {}", i).c_str());
					if (ImGui::BeginPopupModal(fmt::format("Load Texture Window {}", i).c_str()))
					{
						ImGui::Text("test");
						ImGui::EndPopup();
					}
					ImGui::EndPopup();
				}

				if (selected)
				{
					m_selected = i;
					if (ImGui::IsMouseDoubleClicked(0))
					{
						changeFolder();
					}
				}
			}
			ImGui::EndTable();
		}
	}
	ImGui::End();
}
