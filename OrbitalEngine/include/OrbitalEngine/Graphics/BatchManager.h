#pragma once

#include "OrbitalEngine/Graphics/Batch.h"

namespace Orbital
{
	class BatchContainer
	{
	public:
		BatchContainer(const WeakRef<Material>& material);

		void RegisterMesh(MeshRenderer& mr, Transform& t);
		void DeleteMesh(MeshRenderer& mr);
		void RenderBatches();

		const std::vector<Ref<Batch>>& GetBatches() const { return mBatches; }
		std::vector<Ref<Batch>>::iterator begin() { return mBatches.begin(); }
		std::vector<Ref<Batch>>::iterator end() { return mBatches.end(); }

	private:
		Ref<Material> mMaterial;
		std::vector<Ref<Batch>> mBatches;
	};

	class BatchManager
	{
	public:
		BatchManager();

		void RegisterMesh(MeshRenderer& mr, Transform& t);
		void DeleteMesh(MeshRenderer& mr);
		void RenderBatches();
		void OnUpdate();
		size_t GetCount() const { return mBatchContainers.size(); }
		const Ref<BatchContainer>& getBatch(size_t id) const { return mBatchContainers[id]; }

		const std::vector<Ref<BatchContainer>>& GetBatchContainers() const { return mBatchContainers; }
		std::vector<Ref<BatchContainer>>::iterator begin() { return mBatchContainers.begin(); }
		std::vector<Ref<BatchContainer>>::iterator end() { return mBatchContainers.end(); }

	private:
		std::vector<Ref<BatchContainer>> mBatchContainers;
	};
}
