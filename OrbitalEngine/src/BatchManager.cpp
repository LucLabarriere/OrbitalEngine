#include "OrbitalEngine/Graphics/BatchManager.h"
#include "OrbitalEngine/Graphics/MaterialManager.h"
#include "OrbitalEngine/Components/MeshRenderer.h"
#include "OrbitalEngine/Components/Transform.h"


namespace Orbital
{
	constexpr size_t batchsize = 1000;

	BatchContainer::BatchContainer(const WeakRef<Material>& material)
		: mMaterial(material.lock())
	{
		mBatches.push_back(CreateRef<Batch>(material, batchsize));
		mBatches[0]->AllocateMemory();
	}

	void BatchContainer::RegisterMesh(MeshRenderer& mr, Transform& t)
	{
		auto batchData = mr.GetBatchData();

		if (batchData.batch)
		{
			batchData.batch->RegisterMesh(mr, t);
			return;
		}

		for (auto& batch : mBatches)
		{
			bool value = batch->IsFull();

			if (!batch->IsFull())
			{
				if (batch->MeshFits(mr))
				{
					batch->RegisterMesh(mr, t);
					return;
				}
			}
		}

		auto batch = CreateRef<Batch>(mr.GetMaterial(), batchsize);
		mBatches.push_back(batch);
		batch->AllocateMemory();
		batch->RegisterMesh(mr, t);
	}

	void BatchContainer::RenderBatches()
	{
		mMaterial->Bind();


		for (auto& batch : mBatches)
		{
			batch->Render();
		}
	}

	void BatchContainer::DeleteMesh(MeshRenderer& mr)
	{
		for (auto& batch : mBatches)
			batch->DeleteMesh(mr);
	}

	BatchManager::BatchManager()
	{
		mBatchContainers.resize(MaterialManager::GetCount());

		for (auto& material : *MaterialManager::GetInstance())
		{
			mBatchContainers[material->GetId()] = CreateRef<BatchContainer>(material);
		}
	}

	void BatchManager::RegisterMesh(MeshRenderer& mr, Transform& t)
	{
		mBatchContainers[mr.GetMaterial().lock()->GetId()]->RegisterMesh(mr, t);
	}

	void BatchManager::DeleteMesh(MeshRenderer& mr)
	{
		mBatchContainers[mr.GetMaterial().lock()->GetId()]->DeleteMesh(mr);
	}

	void BatchManager::RenderBatches()
	{
		for (auto& batch : mBatchContainers)
		{
			batch->RenderBatches();
		}
	}
}
