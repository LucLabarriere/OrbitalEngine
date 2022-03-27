#include "OrbitalEngine/Graphics/BatchManager.h"
#include "OrbitalEngine/Graphics/MeshManager.h"
#include "OrbitalEngine/Graphics/Renderer.h"
#include "OrbitalEngine/Components/Transform.h"
#include "OrbitalEngine/Components/MeshRenderer.h"

namespace OrbitalEngine
{
	void BatchManager::RegisterMesh(
		Components::MeshRenderer& meshRenderer, Components::Transform& transform)
	{
		if (meshRenderer.StaticDraw && meshRenderer.BatchedDraw)
			RegisterStaticBatchedMesh(meshRenderer, transform);
		else if (meshRenderer.StaticDraw && !meshRenderer.BatchedDraw)
			RegisterStaticMesh(meshRenderer, transform);
		else if (!meshRenderer.StaticDraw && !meshRenderer.BatchedDraw)
			RegisterDynamicMesh(meshRenderer, transform);
		else
			RegisterDynamicBatchedMesh(meshRenderer, transform);
	}

	void BatchManager::RegisterStaticMesh(
		Components::MeshRenderer& meshRenderer,
		const Components::Transform& transform)
	{
		if (!meshRenderer.Batch || meshRenderer.Batch->getRenderMode() != RenderMode::STATIC_NOT_BATCHED)
		{
			const auto& vertices = meshRenderer.Mesh->getVertices();
			const auto& indices = meshRenderer.Mesh->getIndices();

			size_t index = s_static.size();
			s_static.push_back(CreateRef<Batch>(RenderMode::STATIC_BATCHED, vertices.getCount(), indices.getCount()));
			meshRenderer.Batch = s_static[index];
			meshRenderer.Batch->addMesh(meshRenderer.Mesh, transform);
			meshRenderer.Batch->allocateMemory();
		}

		meshRenderer.Batch->requestDraw();
	}

	void BatchManager::RegisterStaticBatchedMesh(
		Components::MeshRenderer& meshRenderer,
		const Components::Transform& transform)
	{
		// TODO: if transform modified, update vertices
		if (!meshRenderer.Batch || meshRenderer.Batch->getRenderMode() != RenderMode::STATIC_BATCHED)
		{
			const auto& vertices = meshRenderer.Mesh->getVertices();
			const auto& indices = meshRenderer.Mesh->getIndices();
			for (size_t i = 0; i < s_staticBatched.size(); i++)
			{
				if (s_staticBatched[i]->getAvailableVertexCount() >= vertices.getCount())
				{
					meshRenderer.Batch = s_staticBatched[i];
					break;
				}
			}

			if (!meshRenderer.Batch)
			{
				Logger::Trace("BatchManager: Creating static Batch");
				size_t index = s_staticBatched.size();
				s_staticBatched.push_back(CreateRef<Batch>(RenderMode::STATIC_BATCHED, s_batchMaxVertexCount, s_batchMaxVertexCount * 3));
				meshRenderer.Batch = s_staticBatched[index];
				meshRenderer.Batch->allocateMemory();
			}

			meshRenderer.Batch->addMesh(meshRenderer.Mesh, transform);
			meshRenderer.Batch->submitData();
		}

		else if (meshRenderer.Batch->isFlushRequested())
		{
			meshRenderer.Batch->flush();
			meshRenderer.Batch->addMesh(meshRenderer.Mesh, transform);
			meshRenderer.Batch->submitData();
		}

		meshRenderer.Batch->requestDraw();
	}

	void BatchManager::RegisterDynamicMesh(
		Components::MeshRenderer& meshRenderer,
		const Components::Transform& transform)
	{

		if (!meshRenderer.Batch || meshRenderer.Batch->getRenderMode() != RenderMode::DYNAMIC_NOT_BATCHED)
		{
			const auto& vertices = meshRenderer.Mesh->getVertices();
			const auto& indices = meshRenderer.Mesh->getIndices();

			size_t index = s_dynamic.size();
			s_dynamic.push_back(CreateRef<Batch>(RenderMode::DYNAMIC_NOT_BATCHED, vertices.getCount(), indices.getCount()));
			meshRenderer.Batch = s_dynamic[index];
			meshRenderer.Batch->addMesh(meshRenderer.Mesh, transform);
			meshRenderer.Batch->allocateMemory();
			meshRenderer.Batch->submitData();
		}
		else
		{
			meshRenderer.Batch->flush();
			meshRenderer.Batch->addMesh(meshRenderer.Mesh, transform);
			meshRenderer.Batch->submitData();
		}

		meshRenderer.Batch->requestDraw();
	}

	void BatchManager::RegisterDynamicBatchedMesh(
		Components::MeshRenderer& meshRenderer,
		const Components::Transform& transform)
	{
		const auto& vertices = meshRenderer.Mesh->getVertices();
		const auto& indices = meshRenderer.Mesh->getIndices();

		if (s_dynamicBatched->getAvailableVertexCount() < vertices.getCount())
		{
			s_dynamicBatched->bind();
			s_dynamicBatched->submitData();
			Renderer::Submit(s_dynamicBatched);
			s_dynamicBatched->flush();
		}

		meshRenderer.Batch = s_dynamicBatched;
		meshRenderer.Batch->addMesh(meshRenderer.Mesh, transform);
		meshRenderer.Batch->requestDraw();
	}

	void BatchManager::RenderBatches()
	{
		// Static Not batched
		for (int i = s_static.size() - 1; i >= 0; i--)
		{
			if (s_static[i] == nullptr)
				s_static.erase(s_static.begin() + i);
			else if (s_static[i]->isDrawRequested())
				Renderer::Submit(s_static[i]);
		}

		// Static Batched
		for (int i = s_staticBatched.size() - 1; i >= 0; i--)
		{
			if (s_staticBatched[i]->isDrawRequested())
				Renderer::Submit(s_staticBatched[i]);
		}

		// Dynamic Not Batched
		for (int i = s_dynamic.size() - 1; i >= 0; i--)
		{
			if (s_dynamic[i] == nullptr)
				s_dynamic.erase(s_dynamic.begin() + i);
			else if (s_dynamic[i]->isDrawRequested())
				Renderer::Submit(s_dynamic[i]);
		}

		// Dynamic Batched
		s_dynamicBatched->bind();
		s_dynamicBatched->submitData();
		Renderer::Submit(s_dynamicBatched);
		s_dynamicBatched->flush();
	}

}