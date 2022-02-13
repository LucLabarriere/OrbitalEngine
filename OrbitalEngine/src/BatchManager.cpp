#include "OrbitalEngine/BatchManager.h"
#include "OrbitalEngine/MeshManager.h"
#include "OrbitalEngine/Components.h"

namespace OrbitalEngine
{
	void BatchManager::RegisterMesh(
		Components::MeshRenderer& meshRenderer,
		const Components::Transform& transform)
	{
		if (meshRenderer.staticDraw && meshRenderer.batchedDraw)
		{
			RegisterStaticBatchedMesh(meshRenderer, transform);
		}

		else if (meshRenderer.staticDraw && !meshRenderer.batchedDraw)
		{
			RegisterStaticMesh(meshRenderer, transform);
		}

		else if (!meshRenderer.staticDraw && !meshRenderer.batchedDraw)
		{
			RegisterDynamicMesh(meshRenderer, transform);
		}

		else
		{
			RegisterDynamicBatchedMesh(meshRenderer, transform);
		}
	}

	void BatchManager::RegisterStaticMesh(
		Components::MeshRenderer& meshRenderer,
		const Components::Transform& transform)
	{
		// TODO
		// Upon removal of entity, reset the Ref<Batch>.
		// On render test if Batch == nullptr, if so delete the entry from the vector
		if (!meshRenderer.Batch)
		{
			const auto& vertices = meshRenderer.Mesh->getVertices();
			const auto& indices = meshRenderer.Mesh->getIndices();

			size_t index = s_static.size();
			s_static.push_back(CreateRef<Batch>(vertices.getCount(), indices.getCount(), true));
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
		if (!meshRenderer.Batch)
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
				s_staticBatched.push_back(CreateRef<Batch>(s_batchMaxVertexCount, s_batchMaxVertexCount * 3, true));
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

		if (!meshRenderer.Batch)
		{
			const auto& vertices = meshRenderer.Mesh->getVertices();
			const auto& indices = meshRenderer.Mesh->getIndices();

			size_t index = s_dynamic.size();
			s_dynamic.push_back(CreateRef<Batch>(vertices.getCount(), indices.getCount(), false));
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

		meshRenderer.Batch = s_dynamicBatched;
		meshRenderer.Batch->addMesh(meshRenderer.Mesh, transform);
		meshRenderer.Batch->allocateMemory();
		meshRenderer.Batch->requestDraw();
	}

	void BatchManager::RenderBatches()
	{
		// TODO replace by Renderer calls

		// Static Not batched
		for (int i = s_static.size() - 1; i >= 0; i--)
		{
			if (s_static[i] == nullptr)
				s_static.erase(s_static.begin() + i);
			else if (s_static[i]->isDrawRequested())
			{
				s_static[i]->bind();
				glad_glDrawElements(GL_TRIANGLES, s_static[i]->getIndexContainerCount(), GL_UNSIGNED_INT, nullptr);
				s_static[i]->requestDraw(false);
			}
		}

		// Static Batched
		for (int i = s_staticBatched.size() - 1; i >= 0; i--)
		{
			if (s_staticBatched[i]->isDrawRequested())
			{
				s_staticBatched[i]->bind();
				glad_glDrawElements(GL_TRIANGLES, s_staticBatched[i]->getIndexContainerCount(), GL_UNSIGNED_INT, nullptr);
				s_staticBatched[i]->requestDraw(false);
			}
		}

		// Dynamic Not Batched
		for (int i = s_dynamic.size() - 1; i >= 0; i--)
		{
			if (s_dynamic[i] == nullptr)
				s_dynamic.erase(s_dynamic.begin() + i);
			else if (s_dynamic[i]->isDrawRequested())
			{
				s_dynamic[i]->bind();
				glad_glDrawElements(GL_TRIANGLES, s_dynamic[i]->getIndexContainerCount(), GL_UNSIGNED_INT, nullptr);
				s_dynamic[i]->requestDraw(false);
			}
		}

		// Dynamic Batched
		s_dynamicBatched->bind();
		s_dynamicBatched->submitData();
		glad_glDrawElements(GL_TRIANGLES, s_dynamicBatched->getIndexContainerCount(), GL_UNSIGNED_INT, nullptr);
		s_dynamicBatched->flush();
	}

}