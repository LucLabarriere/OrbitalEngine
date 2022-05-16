#pragma once

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
			int vertexPointer = -1;
			int indexPointer = -1;
			Components::Transform* Transform = nullptr;

			MeshRenderer(const std::string& meshTag, Components::Transform* transform)
				: Mesh(MeshManager::Get(meshTag)), Transform(transform) { }
			void destroy() { Renderer::DeleteMesh(*this); }

			void setMesh(const std::string& tag)
			{
				destroy();
				Transform->dirty();
				this->Mesh = MeshManager::Get(tag);
			}

		};
	}
}