#pragma once

#include "OrbitalEngine/Graphics/Batch.h"

namespace OrbitalEngine
{
	namespace Components
	{
		struct Transform
		{
			Vec3 Position;
			Vec3 Rotation;
			Vec3 Scale;
		};

		struct MeshRenderer
		{
			Ref<OrbitalEngine::Mesh> Mesh;
			bool StaticDraw = true;
			bool BatchedDraw = false;
			Ref<OrbitalEngine::Batch> Batch = nullptr;
		};
	}
}
