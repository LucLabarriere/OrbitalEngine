#pragma once
#include "OrbitalEngine/Batch.h"
#include "OrbitalEngine/Tools.h"

namespace OrbitalEngine
{
	class BatchManager
	{
	public:
		inline static void Initialize()
		{
			s_dynamicBatched = CreateRef<Batch>(s_batchMaxVertexCount, s_batchMaxVertexCount * 3, false);
			s_dynamicBatched->allocateMemory();
		}

		static void RenderBatches();
		static void RegisterMesh(
			Components::MeshRenderer& meshRenderer, const Components::Transform& transform);

	private:

		static void RegisterStaticMesh(
			Components::MeshRenderer& meshRenderer, const Components::Transform& transform);
		static void RegisterStaticBatchedMesh(
			Components::MeshRenderer& meshRenderer, const Components::Transform& transform);
		static void RegisterDynamicMesh(
			Components::MeshRenderer& meshRenderer, const Components::Transform& transform);
		static void RegisterDynamicBatchedMesh(
			Components::MeshRenderer& meshRenderer, const Components::Transform& transform);

	private:
		inline static std::vector<Ref<Batch>> s_static;
		inline static std::vector<Ref<Batch>> s_dynamic;
		inline static std::vector<Ref<Batch>> s_staticBatched;
		inline static Ref<Batch> s_dynamicBatched;
		const inline static size_t s_batchMaxVertexCount = 1000;
	};
}