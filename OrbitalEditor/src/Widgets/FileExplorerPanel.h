#pragma once

using namespace Orbital;

class FileExplorerPanel
{
public:
	FileExplorerPanel();

	void updateFiles();
	void changeFolder();
	unsigned int getIconIndex(const std::string& fileName);
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
