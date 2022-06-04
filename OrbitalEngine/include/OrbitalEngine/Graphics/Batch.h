#pragma once

#include "OrbitalEngine/Utils.h"
#include "OrbitalEngine/Graphics/Vertices.h"
#include "OrbitalEngine/Graphics/IndexContainer.h"

namespace Orbital
{
	class VertexArray;
	class VertexBuffer;
	class IndexBuffer;
	class Material;
	class MeshRenderer;
	class Transform;

	struct BufferSubData
	{
		size_t firstIndex;
		size_t lastIndex;

		size_t GetStride() const { return lastIndex - firstIndex + 1; }
	};

	class Batch : public std::enable_shared_from_this<Batch>
	{
	public:
		Batch(WeakRef<Material>& material, size_t vertexCount, size_t indexCount = 0);

		void Bind() const;
		void BindMaterial() const;
		void AllocateMemory() const;
		void SubmitData() const;
		void Render();
		void RegisterMesh(MeshRenderer& mr, Transform& t);
		void DeleteMesh(MeshRenderer& mr);
		bool MeshFits(MeshRenderer& mr);

		const BasicVertexContainer& GetVertices() const { return mVertices; }
		const std::vector<bool>& GetFreeVerticesList() const { return mFreeVertices; }
		std::tuple<int, int> GetAvailableSlot(size_t vertexCount, size_t indexCount, bool record = true);
		bool IsFull() const { return mFull; }

	private:
		void updateFullStatus();

	private:
		Ref<VertexArray> mVao;
		Ref<VertexBuffer> mVbo;
		Ref<IndexBuffer> mIbo;
		WeakRef<Material> mMaterial;

		BasicVertexContainer mVertices;
		IndexContainer mIndices;
		
		std::vector<bool> mFreeVertices;
		std::vector<BufferSubData> mSubDataFreeVertices;
		std::vector<BufferSubData> mSubDataFreeIndices;
		std::vector<BufferSubData> mSubDataVertices;
		std::vector<BufferSubData> mSubDataIndices;
		BufferSubData* mCurrentSubDataVertices = nullptr;
		BufferSubData* mCurrentSubDataIndices = nullptr;

		bool mFull = false;
		unsigned int mRenderMode;
	};
}