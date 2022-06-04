#pragma once

#include "OrbitalEngine/Graphics/Batch.h"

namespace Orbital
{
	class BatchContainer
	{
	public:
		BatchContainer(const WeakRef<Material>& material);

		void registerMesh(MeshRenderer& mr, Transform& t);
		void deleteMesh(MeshRenderer& mr);
		void renderBatches();

		const std::vector<Ref<Batch>>& getBatches() const { return m_batches; }
		std::vector<Ref<Batch>>::iterator begin() { return m_batches.begin(); }
		std::vector<Ref<Batch>>::iterator end() { return m_batches.end(); }

	private:
		Ref<Material> m_material;
		std::vector<Ref<Batch>> m_batches;
	};

	class BatchManager
	{
	public:
		BatchManager();

		void registerMesh(MeshRenderer& mr, Transform& t);
		void deleteMesh(MeshRenderer& mr);
		void renderBatches();
		void onUpdate();
		size_t getCount() const { return m_batchContainers.size(); }
		const Ref<BatchContainer>& getBatch(size_t id) const { return m_batchContainers[id]; }

		const std::vector<Ref<BatchContainer>>& getBatchContainers() const { return m_batchContainers; }
		std::vector<Ref<BatchContainer>>::iterator begin() { return m_batchContainers.begin(); }
		std::vector<Ref<BatchContainer>>::iterator end() { return m_batchContainers.end(); }

	private:
		std::vector<Ref<BatchContainer>> m_batchContainers;
	};
}
