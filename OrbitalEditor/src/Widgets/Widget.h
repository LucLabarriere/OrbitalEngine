#pragma once

#include "OrbitalEngine/Logic/Scene.h"

class Widget
{
public:
	static void SetActiveScene(Orbital::Scene** activeScene) { sActiveScene = activeScene; }

protected:
	static inline Orbital::Scene** sActiveScene;
};
