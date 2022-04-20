#pragma once

#include "OrbitalEngine/Graphics/DynamicBatch.h"
#include "OrbitalEngine/Graphics/Batch.h"
#include "OrbitalEngine/Graphics/MaterialManager.h"
#include "OrbitalEngine/Graphics/MeshManager.h"
#include "OrbitalEngine/Graphics/Renderer.h"

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
			Ref<DynamicBatch> DynamicBatch = nullptr;
			int vertexPointer = -1;
			int indexPointer = -1;

			MeshRenderer(const std::string& meshTag) : Mesh(MeshManager::Get(meshTag)) { }

			void destroy() { Renderer::DeleteMesh(*this); }
		};
	}
}