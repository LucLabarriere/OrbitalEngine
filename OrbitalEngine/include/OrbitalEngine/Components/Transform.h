#pragma once

#include "OrbitalEngine/Utils/Misc.h"

namespace Orbital
{
	namespace Components
	{
		struct Transform
		{
			Vec3 Position = { 0.0f, 0.0f, 0.0f};
			Vec3 Rotation = { 0.0f, 0.0f, 0.0f};
			Vec3 Scale = { 1.0f, 1.0f, 1.0f};
		};
	}
}
