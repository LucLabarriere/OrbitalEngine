#include "OrbitalEngine/Graphics/BatchManager.h"
#include "OrbitalEngine/Graphics/MaterialManager.h"
#include "OrbitalEngine/Components.h"


namespace Orbital
{
	constexpr size_t batchsize = 1000;

	BatchContainer::BatchContainer(const WeakRef<Material>& material)
		: m_material(material.lock())
	{
		m_batches.push_back(CreateRef<Batch>(material, batchsize));
		m_batches[0]->allocateMemory();
	}

	void BatchContainer::registerMesh(Components::MeshRenderer& mr, Components::Transform& t)
	{
		auto batchData = mr.getBatchData();
		if (batchData.batch)
		{
			batchData.batch->registerMesh(mr, t);
			return;
		}
		for (auto& batch : m_batches)
		{
			bool value = batch->isFull();

			if (!batch->isFull())
			{
				if (batch->meshFits(mr))
				{
					batch->registerMesh(mr, t);
					return;
				}
			}
		}

		auto batch = CreateRef<Batch>(mr.getMaterial(), batchsize);
		m_batches.push_back(batch);
		batch->allocateMemory();
		batch->registerMesh(mr, t);
	}

	void BatchContainer::renderBatches()
	{
		m_material->bind();


		for (auto& batch : m_batches)
		{
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
		m_batchContainers.resize(MaterialManager::GetCount());

		for (auto& material : *MaterialManager::GetInstance())
		{
			m_batchContainers[material->getId()] = CreateRef<BatchContainer>(material);
		}
	}

	void BatchManager::registerMesh(Components::MeshRenderer& mr, Components::Transform& t)
	{
		m_batchContainers[mr.getMaterial().lock()->getId()]->registerMesh(mr, t);
	}

	void BatchManager::deleteMesh(Components::MeshRenderer& mr)
	{
		m_batchContainers[mr.getMaterial().lock()->getId()]->deleteMesh(mr);
	}

	void BatchManager::renderBatches()
	{
		for (auto& batch : m_batchContainers)
		{
			batch->renderBatches();
		}
	}
}
