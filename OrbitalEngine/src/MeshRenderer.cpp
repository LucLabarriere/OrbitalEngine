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
			: mMesh(MeshManager::Get(meshTag))
			, mMaterial(MaterialManager::Get("Blank"))
			, mTransform(transform)
	{

	}

	MeshRenderer::MeshRenderer(const std::string& meshTag, Transform* transform, bool batchedDraw)
		: mMesh(MeshManager::Get(meshTag))
		, mMaterial(MaterialManager::Get("Blank"))
		, mTransform(transform)
	{
		mDrawData.batchDraw = batchedDraw;
	}

	MeshRenderer::MeshRenderer(const std::string& meshTag,
		Transform* transform, bool batchedDraw,
		const std::string& materialTag)
		: mMesh(MeshManager::Get(meshTag))
		, mTransform(transform)
		, mMaterial(MaterialManager::Get(materialTag))
	{
		mDrawData.batchDraw = batchedDraw;
	}

	MeshRenderer::MeshRenderer(const MeshRenderer& other, Transform* transform)
		: mMesh(other.GetMesh())
		, mTransform(transform)
		, mMaterial(other.GetMaterial())
	{
		mDrawData.hidden = other.GetDrawData().hidden;
		mDrawData.batchDraw = other.GetDrawData().batchDraw;
		mDrawData.staticDraw = other.GetDrawData().staticDraw;
	}

	void MeshRenderer::Destroy()
	{
		Renderer::DeleteMesh(*this);
	}

	void MeshRenderer::SetMesh(const std::string& tag)
	{
		Destroy();
		mBatchData = BatchData();
		mTransform->Dirty();
		mMesh = MeshManager::Get(tag);
	}

	MeshRenderer::DrawData MeshRenderer::GetDrawData() const
	{
		return mDrawData;
	}

	MeshRenderer::BatchData MeshRenderer::GetBatchData() const
	{
		return mBatchData;
	}

	WeakRef<Material> MeshRenderer::GetMaterial() const
	{
		return mMaterial;
	}

	WeakRef<Mesh> MeshRenderer::GetMesh() const
	{
		return mMesh;
	}

	void MeshRenderer::SetBatchData(const BatchData& data)
	{
		mBatchData = data;
	}

	void MeshRenderer::ResetBatchData(const BatchData& data)
	{
		Destroy();
		SetBatchData(data);
	}

	void MeshRenderer::SetDrawData(const DrawData& data)
	{
		Destroy();
		mDrawData = data;
		mBatchData = BatchData();
	}

	void MeshRenderer::SetHidden(bool value)
	{
		mDrawData.hidden = value;
	}

	void MeshRenderer::SetMaterial(const std::string& materialTag)
	{
		Destroy();
		mMaterial = MaterialManager::Get(materialTag);
		mBatchData = BatchData();
	}
}