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

	namespace Components
	{
		struct MeshRenderer;
		class Transform;
	}

	class DynamicBatch : public std::enable_shared_from_this<DynamicBatch>
	{
	public:
		DynamicBatch(WeakRef<Material>& material, size_t vertexCount, size_t indexCount = 0);

		void bind() const;
		void bindMaterial() const;
		void allocateMemory() const;
		void submitData() const;
		void render() const;
		void registerMesh(Components::MeshRenderer& mr, Components::Transform& t);
		void deleteMesh(Components::MeshRenderer& mr);

		std::tuple<int, int> getAvailableSlot(size_t vertexCount, size_t indexCount);

	private:
		Ref<VertexArray> m_vao;
		Ref<VertexBuffer> m_vbo;
		Ref<IndexBuffer> m_ibo;
		WeakRef<Material> m_material;

		BasicVertexContainer m_vertices;
		IndexContainer m_indices;
		
		std::vector<bool> m_freeVertices;
		std::vector<bool> m_modifiedVertices;
		std::vector<bool> m_freeIndices;
		std::vector<bool> m_modifiedIndices;

		unsigned int m_renderMode;
	};
}