#pragma once

#include "Widget.h"

using namespace Orbital;

class AssetManagerPanel: public Widget
{
public:
	AssetManagerPanel();

	void render();

private:
	int m_selected = -1;
};
