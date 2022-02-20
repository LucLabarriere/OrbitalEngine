#pragma once

#include "OrbitalEngine/Logic.h"

using namespace OrbitalEngine;

class GameLayer : public Layer
{
public:
	GameLayer() : Layer("Game Layer") { }
	virtual ~GameLayer() override { }

	virtual void update(Time dt) override
	{

	}
};

class MenuLayer : public Layer
{
public:
	MenuLayer() : Layer("Menu Layer") { }
	virtual ~MenuLayer() override { }

	virtual void update(Time dt) override
	{

	}
};
