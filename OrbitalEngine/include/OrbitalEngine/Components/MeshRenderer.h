#pragma once
#include "OrbitalEngine/Graphics/MeshManager.h"
#include "OrbitalEngine/Graphics/MaterialManager.h"
#include "OrbitalEngine/Components/Transform.h"
#include "OrbitalEngine/Components/Component.h"

namespace Orbital
{
	class Batch;

	class MeshRenderer : public Component
	{
	public:
		struct DrawData
		{
			bool staticDraw = false;
			bool batchDraw = true;
			bool hidden = false;

			bool operator==(const DrawData& other);
			bool operator!=(const DrawData& other);
		};

		struct BatchData
		{
			Ref<Batch> batch = nullptr;
			int vertexPointer = -1;
			int indexPointer = -1;
		};

	public:
		MeshRenderer(const std::string& meshTag, Transform* transform);
		MeshRenderer(const std::string& meshTag, Transform* transform, bool batchedDraw);
		MeshRenderer(const std::string& meshTag, Transform* transform, bool batchedDraw, const std::string& materialName);
		MeshRenderer(const MeshRenderer& other, Transform* transform);

		void Destroy();
		void SetMesh(const std::string& tag);

		DrawData GetDrawData() const;
		BatchData GetBatchData() const;
		WeakRef<Material> GetMaterial() const;
		WeakRef<Mesh> GetMesh() const;
		Vec2& GetTexCoordsMultiplicator() { return mTexCoordsMultiplicator; }
		const Vec2& GetTexCoordsMultiplicator() const { return mTexCoordsMultiplicator; }

		void SetBatchData(const BatchData& data);
		void ResetBatchData(const BatchData& data);
		void SetDrawData(const DrawData& data);
		void SetHidden(bool value);
		void SetMaterial(const std::string& materialTag);

	private:
		WeakRef<Mesh> mMesh;
		WeakRef<Material> mMaterial;
		Transform* mTransform;
		Vec2 mTexCoordsMultiplicator = { 1.0f, 1.0f };

		DrawData mDrawData;
		BatchData mBatchData;
	};
}