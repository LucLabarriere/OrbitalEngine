#include "OrbitalEngine/Graphics/BatchManager.h"
#include "OrbitalEngine/Graphics/MaterialManager.h"
#include "OrbitalEngine/Components.h"


namespace Orbital
{
	constexpr size_t batchsize = 2000;

	BatchContainer::BatchContainer(const WeakRef<Material>& material)
	{
		m_batches.push_back(CreateRef<Batch>(material, batchsize));
		m_batches[0]->allocateMemory();
	}

	void BatchContainer::registerMesh(Components::MeshRenderer& mr, Components::Transform& t)
	{
		for (auto& batch : m_batches)
		{
			bool value = batch->isFull();

			if (!batch->isFull() && batch->meshFits(mr))
			{
				batch->registerMesh(mr, t);
				return;
			}
		}
		auto batch = CreateRef<Batch>(mr.Material, batchsize);
		m_batches.push_back(batch);
		batch->allocateMemory();
		batch->registerMesh(mr, t);
	}

	void BatchContainer::renderBatches()
	{
		for (auto& batch : m_batches)
		{
			batch->bindMaterial();
			batch->submitData();
			batch->render();
		}
	}

	void BatchContainer::deleteMesh(Components::MeshRenderer& mr)
	{
		for (auto& batch : m_batches)
			batch->deleteMesh(mr);
	}

	BatchManager::BatchManager()
	{
		auto material = MaterialManager::Get(0);
		for (auto& material2 : *MaterialManager::GetInstance())
		{
			m_batchContainers[material2->getTag()] = CreateRef<BatchContainer>(material);
		}
	}

	void BatchManager::registerMesh(Components::MeshRenderer& mr, Components::Transform& t)
	{
		m_batchContainers[mr.Material.lock()->getTag()]->registerMesh(mr, t);
	}

	void BatchManager::deleteMesh(Components::MeshRenderer& mr)
	{
		m_batchContainers[mr.Material.lock()->getTag()]->deleteMesh(mr);
	}

	void BatchManager::renderBatches()
	{
		for (auto& batch : m_batchContainers)
		{
			batch.second->renderBatches();
		}
	}
}
