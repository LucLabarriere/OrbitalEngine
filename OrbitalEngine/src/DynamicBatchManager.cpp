#include "OrbitalEngine/Graphics/DynamicBatchManager.h"
#include "OrbitalEngine/Graphics/MaterialManager.h"
#include "OrbitalEngine/Components.h"

namespace Orbital
{
	DynamicBatchManager::DynamicBatchManager()
	{
		auto material = MaterialManager::Get(0);
		for (auto& material2 : *MaterialManager::GetInstance())
		{
			m_batches[material2->getTag()] = CreateRef<DynamicBatch>(material, 10000);
			m_batches[material2->getTag()]->allocateMemory();
		}
	}

	void DynamicBatchManager::registerMesh(Components::MeshRenderer& mr, Components::Transform& t)
	{
		// TODO: check here if the batch is large enough
		m_batches[mr.Material.lock()->getTag()]->registerMesh(mr, t);
	}

	void DynamicBatchManager::deleteMesh(Components::MeshRenderer& mr)
	{
		m_batches[mr.Material.lock()->getTag()]->deleteMesh(mr);
	}

	void DynamicBatchManager::renderBatches()
	{
		for (auto& batch : m_batches)
		{
			batch.second->bindMaterial();
			batch.second->submitData();
			batch.second->render();
		}
	}
}
