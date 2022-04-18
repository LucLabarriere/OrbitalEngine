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
		Mesh(const std::string& tag, const BasicVertexContainer& vertices, const IndexContainer& indices)
			: Asset(s_id, tag), m_vertices(vertices), m_indices(indices) { s_id += 1; }

		static Ref<Mesh> Quad(const std::string& tag = "Quad")
		{
			BasicVertex vertex({ -0.5f, -0.5f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 0.0f });

			BasicVertexContainer vertices(
				BasicVertex({ -0.5f, -0.5f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 0.0f }),
				BasicVertex({  0.5f, -0.5f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, -1.0f }, { 1.0f, 0.0f }),
				BasicVertex({ -0.5f,  0.5f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 1.0f }),
				BasicVertex({  0.5f,  0.5f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, -1.0f }, { 1.0f, 1.0f })
			);

			IndexContainer indices({ 0, 1, 2, 1, 2, 3 });

			return Ref<Mesh>(new Mesh(tag, vertices, indices));
		}

		static Ref<Mesh> Cube(const std::string& tag = "Cube")
		{
			BasicVertexContainer vertices(
				// Same X
				BasicVertex({ -0.5f, -0.5f, -0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { -1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f }),
				BasicVertex({ -0.5f,  0.5f, -0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { -1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f }),
				BasicVertex({ -0.5f, -0.5f,  0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { -1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f }),
				BasicVertex({ -0.5f,  0.5f,  0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { -1.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }),

				BasicVertex({  0.5f, -0.5f, -0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }, {  1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f }),
				BasicVertex({  0.5f,  0.5f, -0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }, {  1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f }),
				BasicVertex({  0.5f, -0.5f,  0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }, {  1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f }), 
				BasicVertex({  0.5f,  0.5f,  0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }, {  1.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }),

				// Same Y
				BasicVertex({ -0.5f, -0.5f, -0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, -1.0f, 0.0f }, { 0.0f, 0.0f }),
				BasicVertex({  0.5f, -0.5f, -0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, -1.0f, 0.0f }, { 1.0f, 0.0f }),
				BasicVertex({ -0.5f, -0.5f,  0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, -1.0f, 0.0f }, { 0.0f, 1.0f }),
				BasicVertex({  0.5f, -0.5f,  0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, -1.0f, 0.0f }, { 1.0f, 1.0f }),

				BasicVertex({ -0.5f,  0.5f, -0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f,  1.0f, 0.0f }, { 0.0f, 0.0f }),
				BasicVertex({  0.5f,  0.5f, -0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f,  1.0f, 0.0f }, { 1.0f, 0.0f }),
				BasicVertex({ -0.5f,  0.5f,  0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f,  1.0f, 0.0f }, { 0.0f, 1.0f }),
				BasicVertex({  0.5f,  0.5f,  0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f,  1.0f, 0.0f }, { 1.0f, 1.0f }),

				// Same Z
				BasicVertex({ -0.5f, -0.5f, -0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 0.0f }),
				BasicVertex({  0.5f, -0.5f, -0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, -1.0f }, { 1.0f, 0.0f }),
				BasicVertex({ -0.5f,  0.5f, -0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 1.0f }),
				BasicVertex({  0.5f,  0.5f, -0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, -1.0f }, { 1.0f, 1.0f }),

				BasicVertex({ -0.5f, -0.5f,  0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f,  1.0f }, { 0.0f, 0.0f }),
				BasicVertex({  0.5f, -0.5f,  0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f,  1.0f }, { 1.0f, 0.0f }),
				BasicVertex({ -0.5f,  0.5f,  0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f,  1.0f }, { 0.0f, 1.0f }),
				BasicVertex({  0.5f,  0.5f,  0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f,  1.0f }, { 1.0f, 1.0f })
			);

			IndexContainer indices({
				 0,  1,  2,  1,  2,  3,
				 4,  5,  6,  5,  6,  7,
				 8,  9, 10,  9, 10, 11,
				12, 13, 14, 13, 14, 15,
				16, 17, 18, 17, 18, 19,
				20, 21, 22, 21, 22, 23
			});

			return Ref<Mesh>(new Mesh(tag, vertices, indices));
		}

		static Ref<Mesh> Triangle(const std::string& tag = "Triangle")
		{
			BasicVertexContainer vertices(
				BasicVertex({ -0.5f, -0.5f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 0.0f }),
				BasicVertex({ 0.5f, -0.5f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, -1.0f }, { 1.0f, 0.0f }),
				BasicVertex({ -0.5f,  0.5f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 1.0f })
			);

			IndexContainer indices({ 0, 1, 2 });

			return Ref<Mesh>(new Mesh(tag, vertices, indices));
		}

	private:
		friend MeshManager;

		BasicVertexContainer m_vertices;
		IndexContainer m_indices;

		static inline size_t s_id = 0;
	};
}