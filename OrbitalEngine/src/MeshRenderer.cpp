#include "OrbitalEngine/Components/MeshRenderer.h"
#include "OrbitalEngine/Components/Transform.h"
#include "OrbitalEngine/Graphics/Batch.h"
#include "OrbitalEngine/Graphics/BufferUnit.h"
#include "OrbitalEngine/Graphics/Renderer.h"

namespace Orbital
{
	bool MeshRenderer::DrawData::operator==(const DrawData& other)
	{
		return other.staticDraw == staticDraw and other.batchDraw == batchDraw and other.hidden == hidden;
	}

	bool MeshRenderer::DrawData::operator!=(const DrawData& other)
	{
		return !(other.staticDraw == staticDraw and other.batchDraw == batchDraw and other.hidden == hidden);
	}

	MeshRenderer::MeshRenderer(const std::string& meshTag, Transform* transform)
			: m_mesh(MeshManager::Get(meshTag))
			, m_material(MaterialManager::Get("Blank"))
			, m_transform(transform)
	{

	}

	MeshRenderer::MeshRenderer(const std::string& meshTag, Transform* transform, bool batchedDraw)
		: m_mesh(MeshManager::Get(meshTag))
		, m_material(MaterialManager::Get("Blank"))
		, m_transform(transform)
	{
		m_drawData.batchDraw = batchedDraw;
	}

	MeshRenderer::MeshRenderer(const std::string& meshTag,
		Transform* transform, bool batchedDraw,
		const std::string& materialTag)
		: m_mesh(MeshManager::Get(meshTag))
		, m_transform(transform)
		, m_material(MaterialManager::Get(materialTag))
	{
		m_drawData.batchDraw = batchedDraw;
	}

	MeshRenderer::MeshRenderer(const MeshRenderer& other, Transform* transform)
		: m_mesh(other.getMesh())
		, m_transform(transform)
		, m_material(other.getMaterial())
	{
		m_drawData.hidden = other.getDrawData().hidden;
		m_drawData.batchDraw = other.getDrawData().batchDraw;
		m_drawData.staticDraw = other.getDrawData().staticDraw;
	}

	void MeshRenderer::destroy()
	{
		Renderer::DeleteMesh(*this);
	}

	void MeshRenderer::setMesh(const std::string& tag)
	{
		destroy();
		m_batchData = BatchData();
		m_transform->dirty();
		m_mesh = MeshManager::Get(tag);
	}

	MeshRenderer::DrawData MeshRenderer::getDrawData() const
	{
		return m_drawData;
	}

	MeshRenderer::BatchData MeshRenderer::getBatchData() const
	{
		return m_batchData;
	}

	WeakRef<Material> MeshRenderer::getMaterial() const
	{
		return m_material;
	}

	WeakRef<Mesh> MeshRenderer::getMesh() const
	{
		return m_mesh;
	}

	void MeshRenderer::setBatchData(const BatchData& data)
	{
		m_batchData = data;
	}

	void MeshRenderer::resetBatchData(const BatchData& data)
	{
		destroy();
		setBatchData(data);
	}

	void MeshRenderer::setDrawData(const DrawData& data)
	{
		destroy();
		m_drawData = data;
		m_batchData = BatchData();
	}

	void MeshRenderer::setHidden(bool value)
	{
		m_drawData.hidden = value;
	}

	void MeshRenderer::setMaterial(const std::string& materialTag)
	{
		destroy();
		m_material = MaterialManager::Get(materialTag);
		m_batchData = BatchData();
	}
}