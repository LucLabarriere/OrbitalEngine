#include "OrbitalEngine/Graphics.h"
#include "OrbitalEngine/Components/MeshRenderer.h"
#include "OrbitalEngine/Components/Transform.h"

namespace Orbital
{
	BufferUnitManager::BufferUnitManager()
	{

	}

	void BufferUnitManager::registerMesh(const Components::MeshRenderer& mr, Components::Transform& t)
	{
		auto mesh = mr.getMesh().lock();
		auto material = mr.getMaterial().lock();

		m_data[material->getId()][mesh->getId()].push_back(
			CreateRef<RenderData>(&t, mr.getTexCoordsMultiplicator(), material->getId(), mesh->getId())
		);
	}

	void BufferUnitManager::renderUnits()
	{
		for (auto [materialId, materialTree] : m_data)
		{
			auto material = MaterialManager::Get(materialId).lock();
			material->bind();

			for (auto [meshId, meshTree] : materialTree)
			{
				auto mesh = MeshManager::Get(meshId).lock();
				auto unit = m_units[materialId][meshId];

				unit->bind();

				for (auto renderData : meshTree)
				{
					unit->setModelMatrixUniform(material->getShader(), *(renderData->transform));
					material->getShader().lock()
						->setUniform2f("u_TexCoordsMultiplicator", renderData->texCoordsMultiplicator);
					RenderCommands::DrawIndexed(OE_TRIANGLES, mesh->getIndices().getSize());
					Metrics::IncrementBatchCount();
				}
			}
		}

		m_data.clear();
	}

	void BufferUnitManager::push(WeakRef<Mesh>& mesh)
	{
		for (auto material : *MaterialManager::GetInstance())
		{
			m_units[material->getId()].emplace(
				mesh.lock()->getId(), CreateRef<BufferUnit>(mesh, material)
			);
		}
	}

	void BufferUnitManager::push(WeakRef<Material>& material, bool fill)
	{
		size_t materialId = material.lock()->getId();
		m_units.emplace(materialId, std::unordered_map<size_t, Ref<BufferUnit>>());

		if (fill)
		{
			for (WeakRef<Mesh> mesh : *MeshManager::GetInstance())
			{
				m_units[materialId].emplace(mesh.lock()->getId(), CreateRef<BufferUnit>(mesh, material));

			}
		}
	}

	
}