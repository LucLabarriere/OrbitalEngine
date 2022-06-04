#include "FileExplorerPanel.h"
#include "Tools.h"
#include "OrbitalEngine/Utils/Logger.h"

FileExplorerPanel::FileExplorerPanel()
{
	UpdateFiles();
}

void FileExplorerPanel::UpdateFiles()
{
	mFileCount = std::distance(std::filesystem::directory_iterator(mCurrentDirectory), std::filesystem::directory_iterator());
	mFileNames.resize(mFileCount);

	size_t i = 0;
	const auto& entries = std::filesystem::directory_iterator(mCurrentDirectory);
	for (const auto& entry : entries)
	{
		mFileNames[i] = entry.path().filename().string();
		i += 1;
	}

	mSelected = -1;
}

void FileExplorerPanel::ChangeFolder()
{
	std::filesystem::path newPath = mCurrentDirectory / mFileNames[mSelected];
	Logger::Trace("Path: {}", newPath.string());
	bool isDirectory = std::filesystem::is_directory(newPath);

	if (isDirectory)
	{
		mCurrentDirectory = newPath;
	}

	UpdateFiles();
}

TextureIconIndex FileExplorerPanel::GetIconIndex(const std::string& fileName)
{
	std::filesystem::path filePath(std::filesystem::path(mCurrentDirectory / fileName));
	std::string extension = filePath.extension().string();
	/*if (std::filesystem::is_directory(filePath))
		extension = "folder";*/
	
	if (extension == "folder")
		return TextureIconIndex::Folder;
	else if (extension == ".png" || extension == ".jpeg")
		return TextureIconIndex::Image;
	else if (extension == ".txt")
		return TextureIconIndex::Text;

	return TextureIconIndex::File;
}

void FileExplorerPanel::Render()
{
	if (ImGui::Begin("Files"))
	{
		if (ImGui::Button("<"))
		{
			mCurrentDirectory = mCurrentDirectory.parent_path();
			UpdateFiles();
		}
		ImGui::Text(mCurrentDirectory.parent_path().string().c_str());

		ImGuiTableFlags tableFlags = ImGuiTableFlags_SizingFixedFit | 
			ImGuiTableFlags_ContextMenuInBody | ImGuiTableFlags_NoHostExtendX | ImGuiTableFlags_RowBg;
	
		ImGuiSelectableFlags selectableFlags = ImGuiSelectableFlags_SpanAllColumns | ImGuiSelectableFlags_AllowDoubleClick;

		if (ImGui::BeginTable("File explorer table", 2, tableFlags))
		{
			ImGui::TableSetupColumn("AAA", ImGuiTableColumnFlags_WidthFixed);
			ImGui::TableSetupColumn("BBB", ImGuiTableColumnFlags_WidthStretch);

			for (size_t i = 0; i < mFileNames.size(); i++)
			{
				auto iconIndex = GetIconIndex(mFileNames[i]);
				ImGui::TableNextRow();
				ImGui::TableNextColumn();

				Tools::RenderIcon(iconIndex);
				ImGui::TableNextColumn();

				bool selected = ImGui::Selectable(mFileNames[i].c_str(), mSelected == i, selectableFlags);

				if (iconIndex == TextureIconIndex::Image && ImGui::BeginPopupContextItem(fmt::format("Load Texture {}", i).c_str()))
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
					mSelected = i;

					if (ImGui::IsMouseDoubleClicked(0))
					{
						ChangeFolder();
					}
				}
			}
			ImGui::EndTable();
		}
	}
	ImGui::End();
}
