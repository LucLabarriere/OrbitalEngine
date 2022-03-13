#pragma once

#include "OrbitalEngine/Logic.h"

using namespace OrbitalEngine;

class GuiLayer : public Layer
{
public:
	GuiLayer() : Layer("GUI Layer") { }
	virtual ~GuiLayer() override { }

	virtual void update(Time dt) override
	{

	}
};
