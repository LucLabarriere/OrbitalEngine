#pragma once

#include "Vertices.h"

namespace OrbitalEngine
{
	class MeshManager;

	class Mesh
	{
	public:
		const std::string& getTag() const { return m_tag;  }
		const BasicVertexContainer& getVertices() const { return m_vertices; }
		const IndexContainer& getIndices() const { return m_indices; }

	private:
		Mesh(const std::string& tag, const BasicVertexContainer& vertices,
			const IndexContainer& indices)
			: m_tag(tag), m_vertices(vertices), m_indices(indices) { }

		static Mesh* Quad(const std::string& tag = "Quad")
		{
			BasicVertexContainer vertices(
				BasicVertex({ -0.5f, -0.5f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }),
				BasicVertex({ -0.5f,  0.5f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }),
				BasicVertex({  0.5f, -0.5f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }),
				BasicVertex({  0.5f,  0.5f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f })
			);

			IndexContainer indices({ 0, 1, 2, 1, 2, 3 });

			return new Mesh(tag, vertices, indices);
		}

	private:
		friend MeshManager;

		std::string m_tag;
		BasicVertexContainer m_vertices;
		IndexContainer m_indices;
	};
}