#pragma once

#include "OrbitalEngine/Utils/Misc.h"

namespace Orbital
{
	class Scene;

	class Component
	{
	public:
		Component() { }
		static void SetActiveScene(Scene** scene) { sActiveScene = scene; }

	private:
		static inline Scene** sActiveScene;
	};
}