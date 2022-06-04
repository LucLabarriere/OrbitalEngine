#pragma once

#include "Constants.h"
#include "Widget.h"

using namespace Orbital;

class FileExplorerPanel : public Widget
{
public:
	FileExplorerPanel();

	void updateFiles();
	void changeFolder();
	TextureIconIndex getIconIndex(const std::string& fileName);
	void render();

private:
	struct BoolSelect
	{
		bool value = false;
	};

	std::filesystem::path m_currentDirectory = std::filesystem::absolute(".");
	std::vector<std::string> m_fileNames;
	int m_selected = -1;
	int m_fileCount;
};
