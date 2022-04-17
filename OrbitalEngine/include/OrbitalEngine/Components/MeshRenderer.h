#pragma once

#include "OrbitalEngine/Graphics/Batch.h"
#include "OrbitalEngine/Graphics/MaterialManager.h"
#include "OrbitalEngine/Graphics/MeshManager.h"

namespace Orbital
{
	namespace Components
	{
		struct MeshRenderer
		{
			WeakRef<Mesh> Mesh;
			WeakRef<Material> Material = MaterialManager::Get("Blank");
			bool StaticDraw = false;
			bool BatchedDraw = true;
			bool Hidden = false;
			Ref<Batch> Batch = nullptr;

			MeshRenderer(const std::string& meshTag) : Mesh(MeshManager::Get(meshTag)) { }
		};
	}
}