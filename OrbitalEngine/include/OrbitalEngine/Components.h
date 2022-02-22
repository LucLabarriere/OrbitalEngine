#pragma once

#include "OrbitalEngine/Graphics/Batch.h"

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
			Ref<OrbitalEngine::Mesh> Mesh;
			bool staticDraw = true;
			bool batchedDraw = false;
			Ref<OrbitalEngine::Batch> Batch = nullptr;
		};
	}
}
