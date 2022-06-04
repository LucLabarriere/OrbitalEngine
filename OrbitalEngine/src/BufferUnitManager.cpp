#include "OrbitalEngine/Graphics.h"
#include "OrbitalEngine/Components/MeshRenderer.h"
#include "OrbitalEngine/Components/Transform.h"

namespace Orbital
{
	BufferUnitManager::BufferUnitManager()
	{

	}

	void BufferUnitManager::RegisterMesh(const MeshRenderer& mr, Transform& t)
	{
		auto mesh = mr.GetMesh().lock();
		auto material = mr.GetMaterial().lock();

		mData[material->GetId()][mesh->GetId()].push_back(
			CreateRef<RenderData>(&t, mr.GetTexCoordsMultiplicator(), material->GetId(), mesh->GetId())
		);
	}

	void BufferUnitManager::RenderUnits()
	{
		for (auto [materialId, materialTree] : mData)
		{
			auto material = MaterialManager::Get(materialId).lock();
			material->Bind();

			for (auto [meshId, meshTree] : materialTree)
			{
				auto mesh = MeshManager::Get(meshId).lock();
				auto unit = mUnits[materialId][meshId];

				unit->Bind();

				for (auto renderData : meshTree)
				{
					unit->SetModelMatrixUniform(material->GetShader(), *(renderData->transform));
					material->GetShader().lock()
						->SetUniform2f("u_TexCoordsMultiplicator", renderData->texCoordsMultiplicator);
					RenderCommands::DrawIndexed(OE_TRIANGLES, mesh->getIndices().GetSize());
					Metrics::IncrementBatchCount();
				}
			}
		}

		mData.clear();
	}

	void BufferUnitManager::Push(WeakRef<Mesh>& mesh)
	{
		for (auto material : *MaterialManager::GetInstance())
		{
			mUnits[material->GetId()].emplace(
				mesh.lock()->GetId(), CreateRef<BufferUnit>(mesh, material)
			);
		}
	}

	void BufferUnitManager::Push(WeakRef<Material>& material, bool fill)
	{
		size_t materialId = material.lock()->GetId();
		mUnits.emplace(materialId, std::unordered_map<size_t, Ref<BufferUnit>>());

		if (fill)
		{
			for (WeakRef<Mesh> mesh : *MeshManager::GetInstance())
			{
				mUnits[materialId].emplace(mesh.lock()->GetId(), CreateRef<BufferUnit>(mesh, material));

			}
		}
	}

	
}