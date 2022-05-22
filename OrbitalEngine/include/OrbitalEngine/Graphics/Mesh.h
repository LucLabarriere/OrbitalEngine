#pragma once

#include "OrbitalEngine/Graphics/Vertices.h"
#include "OrbitalEngine/Graphics/IndexContainer.h"

namespace Orbital
{
	class MeshManager;

	class Mesh : public Asset
	{
	public:
		const BasicVertexContainer& getVertices() const { return m_vertices; }
		const IndexContainer& getIndices() const { return m_indices; }

	private:
		Mesh(const std::string& tag, const BasicVertexContainer& vertices, const IndexContainer& indices);

		static Ref<Mesh> Quad(const std::string& tag = "Quad");
		static Ref<Mesh> Cube(const std::string& tag = "Cube");
		static Ref<Mesh> Triangle(const std::string& tag = "Triangle");

	private:
		friend MeshManager;

		BasicVertexContainer m_vertices;
		IndexContainer m_indices;

		static inline size_t s_id = 0;
	};
}