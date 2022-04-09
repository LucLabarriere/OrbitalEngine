#pragma once

using namespace Orbital;

class AssetManagerPanel
{
public:
	AssetManagerPanel();

	void render();

private:
	int m_selected = -1;
};
