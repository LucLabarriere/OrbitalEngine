#pragma once

#include "OrbitalEngine/Graphics/Batch.h"

namespace Orbital
{
	class BatchContainer
	{
	public:
		BatchContainer(const WeakRef<Material>& material);

		void registerMesh(Components::MeshRenderer& mr, Components::Transform& t);
		void deleteMesh(Components::MeshRenderer& mr);
		void renderBatches();

		const std::vector<Ref<Batch>>& getBatches() const { return m_batches; }
		std::vector<Ref<Batch>>::iterator begin() { return m_batches.begin(); }
		std::vector<Ref<Batch>>::iterator end() { return m_batches.end(); }

	private:
		std::vector<Ref<Batch>> m_batches;
	};

	class BatchManager
	{
	public:
		BatchManager();

		void registerMesh(Components::MeshRenderer& mr, Components::Transform& t);
		void deleteMesh(Components::MeshRenderer& mr);
		void renderBatches();

		const std::map<std::string, Ref<BatchContainer>>& getBatchContainers() const { return m_batchContainers; }
		std::map<std::string, Ref<BatchContainer>>::iterator begin() { return m_batchContainers.begin(); }
		std::map<std::string, Ref<BatchContainer>>::iterator end() { return m_batchContainers.end(); }

	private:
		std::map<std::string, Ref<BatchContainer>> m_batchContainers;
	};
}
