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

		size_t getStride() const { return lastIndex - firstIndex + 1; }
	};

	class Batch : public std::enable_shared_from_this<Batch>
	{
	public:
		Batch(WeakRef<Material>& material, size_t vertexCount, size_t indexCount = 0);

		void bind() const;
		void bindMaterial() const;
		void allocateMemory() const;
		void submitData() const;
		void render();
		void registerMesh(MeshRenderer& mr, Transform& t);
		void deleteMesh(MeshRenderer& mr);
		bool meshFits(MeshRenderer& mr);

		const BasicVertexContainer& getVertices() const { return m_vertices; }
		const std::vector<bool>& getFreeVerticesList() const { return m_freeVertices; }
		std::tuple<int, int> getAvailableSlot(size_t vertexCount, size_t indexCount, bool record = true);
		bool isFull() const { return m_full; }

	private:
		void updateFullStatus();

	private:
		Ref<VertexArray> m_vao;
		Ref<VertexBuffer> m_vbo;
		Ref<IndexBuffer> m_ibo;
		WeakRef<Material> m_material;

		BasicVertexContainer m_vertices;
		IndexContainer m_indices;
		
		std::vector<bool> m_freeVertices;
		std::vector<BufferSubData> m_subDataFreeVertices;
		std::vector<BufferSubData> m_subDataFreeIndices;
		std::vector<BufferSubData> m_subDataVertices;
		std::vector<BufferSubData> m_subDataIndices;
		BufferSubData* m_currentSubDataVertices = nullptr;
		BufferSubData* m_currentSubDataIndices = nullptr;

		bool m_full = false;
		unsigned int m_renderMode;
	};
}