#pragma once

#include "OrbitalEngine/Graphics/Vertices.h"
#include "OrbitalEngine/Graphics/IndexContainer.h"

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
				BasicVertex({ -0.5f, -0.5f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f }),
				BasicVertex({  0.5f, -0.5f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 1.0f, 0.0f }),
				BasicVertex({ -0.5f,  0.5f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f }),
				BasicVertex({  0.5f,  0.5f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f })
			);

			IndexContainer indices({ 0, 1, 2, 1, 2, 3 });

			return new Mesh(tag, vertices, indices);
		}

		static Mesh* Cube(const std::string& tag = "Cube")
		{
			BasicVertexContainer vertices(
				// Same X
				BasicVertex({ -0.5f, -0.5f, -0.5f }, { 1.0f, 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f }),
				BasicVertex({ -0.5f,  0.5f, -0.5f }, { 1.0f, 0.0f, 0.0f, 1.0f }, { 1.0f, 0.0f }),
				BasicVertex({ -0.5f, -0.5f,  0.5f }, { 1.0f, 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f }),
				BasicVertex({ -0.5f,  0.5f,  0.5f }, { 1.0f, 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f }),

				BasicVertex({  0.5f, -0.5f, -0.5f }, { 0.0f, 0.0f, 1.0f, 1.0f }, { 0.0f, 0.0f }),
				BasicVertex({  0.5f,  0.5f, -0.5f }, { 0.0f, 0.0f, 1.0f, 1.0f }, { 1.0f, 0.0f }),
				BasicVertex({  0.5f, -0.5f,  0.5f }, { 0.0f, 0.0f, 1.0f, 1.0f }, { 0.0f, 1.0f }),
				BasicVertex({  0.5f,  0.5f,  0.5f }, { 0.0f, 0.0f, 1.0f, 1.0f }, { 1.0f, 1.0f }),

				// Same Y
				BasicVertex({ -0.5f, -0.5f, -0.5f }, { 0.0f, 1.0f, 0.0f, 1.0f }, { 0.0f, 0.0f }),
				BasicVertex({  0.5f, -0.5f, -0.5f }, { 0.0f, 1.0f, 0.0f, 1.0f }, { 1.0f, 0.0f }),
				BasicVertex({ -0.5f, -0.5f,  0.5f }, { 0.0f, 1.0f, 0.0f, 1.0f }, { 0.0f, 1.0f }),
				BasicVertex({  0.5f, -0.5f,  0.5f }, { 0.0f, 1.0f, 0.0f, 1.0f }, { 1.0f, 1.0f }),

				BasicVertex({ -0.5f,  0.5f, -0.5f }, { 1.0f, 1.0f, 0.0f, 1.0f }, { 0.0f, 0.0f }),
				BasicVertex({  0.5f,  0.5f, -0.5f }, { 1.0f, 1.0f, 0.0f, 1.0f }, { 1.0f, 0.0f }),
				BasicVertex({ -0.5f,  0.5f,  0.5f }, { 1.0f, 1.0f, 0.0f, 1.0f }, { 0.0f, 1.0f }),
				BasicVertex({  0.5f,  0.5f,  0.5f }, { 1.0f, 1.0f, 0.0f, 1.0f }, { 1.0f, 1.0f }),

				// Same Z
				BasicVertex({ -0.5f, -0.5f, -0.5f }, { 1.0f, 0.0f, 1.0f, 1.0f }, { 0.0f, 0.0f }),
				BasicVertex({  0.5f, -0.5f, -0.5f }, { 1.0f, 0.0f, 1.0f, 1.0f }, { 1.0f, 0.0f }),
				BasicVertex({ -0.5f,  0.5f, -0.5f }, { 1.0f, 0.0f, 1.0f, 1.0f }, { 0.0f, 1.0f }),
				BasicVertex({  0.5f,  0.5f, -0.5f }, { 1.0f, 0.0f, 1.0f, 1.0f }, { 1.0f, 1.0f }),

				BasicVertex({ -0.5f, -0.5f,  0.5f }, { 0.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f }),
				BasicVertex({  0.5f, -0.5f,  0.5f }, { 0.0f, 1.0f, 1.0f, 1.0f }, { 1.0f, 0.0f }),
				BasicVertex({ -0.5f,  0.5f,  0.5f }, { 0.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f }),
				BasicVertex({  0.5f,  0.5f,  0.5f }, { 0.0f, 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f })
			);

			IndexContainer indices({
				 0,  1,  2,  1,  2,  3,
				 4,  5,  6,  5,  6,  7,
				 8,  9, 10,  9, 10, 11,
				12, 13, 14, 13, 14, 15,
				16, 17, 18, 17, 18, 19,
				20, 21, 22, 21, 22, 23
			});

			return new Mesh(tag, vertices, indices);
		}

	private:
		friend MeshManager;

		std::string m_tag;
		BasicVertexContainer m_vertices;
		IndexContainer m_indices;
	};
}