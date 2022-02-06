#pragma once

#include "OrbitalEngine/Core.h"
#include "GameLayer.h"

using namespace OrbitalEngine;

class GameApplication : public Application
{
public:
	GameApplication() : Application()
	{
		m_layerStack->push(CreateRef<GameLayer>());
		m_layerStack->push(CreateRef<MenuLayer>());
	}

	virtual ~GameApplication() override { };


private:

};