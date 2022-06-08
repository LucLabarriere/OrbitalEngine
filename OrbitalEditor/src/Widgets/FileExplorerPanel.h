#pragma once

#include "Constants.h"
#include "Widget.h"

using namespace Orbital;

class FileExplorerPanel
{
public:
	FileExplorerPanel();

	void UpdateFiles();
	void ChangeFolder();
	TextureIconIndex GetIconIndex(const std::string& fileName);
	void Render();

private:
	struct BoolSelect
	{
		bool value = false;
	};

	std::filesystem::path mCurrentDirectory = std::filesystem::absolute(".");
	std::vector<std::string> mFileNames;
	int mSelected = -1;
	int mFileCount;
};
