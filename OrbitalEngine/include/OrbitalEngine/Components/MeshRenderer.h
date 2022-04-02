#pragma once

#include "OrbitalEngine/Graphics/Batch.h"

namespace Orbital
{
	namespace Components
	{
		struct MeshRenderer
		{
			Ref<Orbital::Mesh> Mesh;
			bool StaticDraw = true;
			bool BatchedDraw = false;
			bool Hidden = false;
			Ref<Orbital::Batch> Batch = nullptr;
		};
	}
}