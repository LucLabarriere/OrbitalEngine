#pragma once

#include "BatchManager.h"

namespace OrbitalEngine
{
	namespace Components
	{
		struct Transform
		{
			glm::vec3 Position;
			glm::vec3 Rotation;
			glm::vec3 Scale;
		};

		struct MeshRenderer
		{
			Ref<Mesh> Mesh;
			bool staticDraw = true;
			bool batchedDraw = false;
			Ref<Batch> Batch = nullptr;
		};
	}
}
