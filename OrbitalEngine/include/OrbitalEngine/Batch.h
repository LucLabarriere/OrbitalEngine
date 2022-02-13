#pragma once
#pragma warning(push)
#pragma warning(disable : 4661)

#include "OrbitalEngine/Tools.h"
#include "OrbitalEngine/IndexContainer.h"
#include "OrbitalEngine/MeshManager.h"
#include "OrbitalEngine/Vertices.h"

namespace OrbitalEngine
{
	class VertexArray;
	class VertexBuffer;
	class IndexBuffer;

	namespace Components
	{
		class Transform;
		class MeshRenderer;
	}

	class Batch
	{
	public:
		Batch(size_t count, size_t indexCount = 0, bool staticDraw = true);

		void bind() const;
		void allocateMemory() const;
		void submitData() const;
		void requestDraw(bool request = true);
		void requestFlush(bool request = true);
		void flush();

		void addMesh(const std::string& meshTag, const Components::Transform& transform);
		void addMesh(const Ref<Mesh>& mesh, const Components::Transform& transform);
		
		size_t getVertexContainerCount() const;
		size_t getVertexContainerSize() const;
		size_t getIndexContainerCount() const;
		size_t getIndexContainerSize() const;
		size_t getAvailableVertexCount() const;
		size_t getAvailableIndexCount() const;
		bool isDrawRequested() const { return m_requestDraw; }
		bool isFlushRequested() const { return m_requestFlush; }

	private:
		bool m_staticDraw = true;
		bool m_requestDraw = false;
		bool m_requestFlush = false;
		size_t m_maxVertexContainerCount;
		size_t m_maxIndexContainerCount;
		size_t m_maxVertexContainerSize;
		size_t m_maxIndexContainerSize;

		BasicVertexContainer m_vertices;
		IndexContainer m_indices;
		
		size_t m_currentVertex = 0;
		size_t m_currentIndex = 0;

		Ref<VertexArray> m_vao;
		Ref<VertexBuffer> m_vbo;
		Ref<IndexBuffer> m_ibo;
	};
}
#pragma warning(pop)