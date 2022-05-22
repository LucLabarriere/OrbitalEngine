#include "OrbitalEngine/Graphics/Mesh.h"

namespace Orbital
{
	inline static const float offset = 0.0005f;

	Mesh::Mesh(const std::string& tag, const BasicVertexContainer& vertices, const IndexContainer& indices)
		: Asset(s_id, tag), m_vertices(vertices), m_indices(indices)
	{
		s_id += 1;
	}

	Ref<Mesh> Mesh::Quad(const std::string& tag)
	{
		BasicVertexContainer vertices(
			BasicVertex({ -0.5f, -0.5f,  offset }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f,  1.0f }, { 0.0f, 0.0f }),
			BasicVertex({  0.5f, -0.5f,  offset }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f,  1.0f }, { 1.0f, 0.0f }),
			BasicVertex({ -0.5f,  0.5f,  offset }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f,  1.0f }, { 0.0f, 1.0f }),
			BasicVertex({  0.5f,  0.5f,  offset }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f,  1.0f }, { 1.0f, 1.0f }),

			BasicVertex({ -0.5f, -0.5f, -offset }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 0.0f }),
			BasicVertex({  0.5f, -0.5f, -offset }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, -1.0f }, { 1.0f, 0.0f }),
			BasicVertex({ -0.5f,  0.5f, -offset }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 1.0f }),
			BasicVertex({  0.5f,  0.5f, -offset }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, -1.0f }, { 1.0f, 1.0f })
		);

		IndexContainer indices({ 0, 1, 2, 1, 2, 3, 4, 5, 6, 5, 6, 7 });

		return Ref<Mesh>(new Mesh(tag, vertices, indices));
	}

	Ref<Mesh> Mesh::Cube(const std::string& tag)
	{
		BasicVertexContainer vertices(
			// Same X
			BasicVertex({ -0.5f, -0.5f, -0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { -1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f }),
			BasicVertex({ -0.5f,  0.5f, -0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { -1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f }),
			BasicVertex({ -0.5f, -0.5f,  0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { -1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f }),
			BasicVertex({ -0.5f,  0.5f,  0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { -1.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }),

			BasicVertex({ 0.5f, -0.5f, -0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f }),
			BasicVertex({ 0.5f,  0.5f, -0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f }),
			BasicVertex({ 0.5f, -0.5f,  0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f }),
			BasicVertex({ 0.5f,  0.5f,  0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 1.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }),

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

	Ref<Mesh> Mesh::Triangle(const std::string& tag)
	{
		BasicVertexContainer vertices(
			BasicVertex({ -0.5f, -0.5f, -offset }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 0.0f }),
			BasicVertex({  0.5f, -0.5f, -offset }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, -1.0f }, { 1.0f, 0.0f }),
			BasicVertex({ -0.5f,  0.5f, -offset }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 1.0f }),
			BasicVertex({ -0.5f, -0.5f,  offset }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f,  1.0f }, { 0.0f, 0.0f }),
			BasicVertex({  0.5f, -0.5f,  offset }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f,  1.0f }, { 1.0f, 0.0f }),
			BasicVertex({ -0.5f,  0.5f,  offset }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f,  1.0f }, { 0.0f, 1.0f })
		);

		IndexContainer indices({ 0, 1, 2, 3, 4, 5 });

		return Ref<Mesh>(new Mesh(tag, vertices, indices));
	}
}