#pragma once

#include "Widget.h"

using namespace Orbital;

class AssetManagerPanel: public Widget
{
public:
	AssetManagerPanel();

	void Render();

private:
	int mSelected = -1;
};
