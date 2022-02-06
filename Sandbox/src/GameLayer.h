#pragma once

#include "OrbitalEngine/Layer.h"

using namespace OrbitalEngine;

class GameLayer : public Layer
{
public:
	GameLayer() : Layer("Game Layer") { }
	virtual ~GameLayer() override { }

	virtual void update(Time dt) override
	{

	}

	virtual bool onKeyPressed(KeyPressedEvent& e) override
	{
		Logger::Info("Game Layer: {}", e.getKeyCode());
		return false;
	}

	virtual bool onMouseScrolled(MouseScrolledEvent& e) override
	{
		Logger::Info("Game Layer: {}", e.getX(), e.getY());
		return true;
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

	virtual bool onKeyPressed(KeyPressedEvent& e) override
	{
		Logger::Info("Menu Layer: {}", e.getKeyCode());
		return false;
	}

	virtual bool onMouseScrolled(MouseScrolledEvent& e) override
	{
		Logger::Info("Menu Layer: {}", e.getX(), e.getY());
		return true;
	}
};
