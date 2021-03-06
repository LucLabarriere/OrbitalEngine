#include "OrbitalEngine/Graphics/Mesh.h"

namespace Orbital
{
	inline static const float offset = 0.0005f;

	Mesh::Mesh(const std::string& tag, const BasicVertexContainer& vertices, const IndexContainer& indices)
		: Asset(sId, tag), mVertices(vertices), mIndices(indices)
	{
		sId += 1;
	}

	Ref<Mesh> Mesh::Quad(const std::string& tag)
	{
		BasicVertexContainer vertices(
			BasicVertex({ -0.5f, -0.5f,  offset }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f,  1.0f }, { 0.0f, 0.0f }),
			BasicVertex({  0.5f, -0.5f,  offset }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f,  1.0f }, { 1.0f, 0.0f }),
			BasicVertex({ -0.5f,  0.5f,  offset }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f,  1.0f }, { 0.0f, 1.0f }),
			BasicVertex({  0.5f,  0.5f,  offset }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f,  1.0f }, { 1.0f, 1.0f }),

			BasicVertex({ -0.5f, -0.5f, -offset }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 0.0f }),
			BasicVertex({ -0.5f,  0.5f, -offset }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 1.0f }),
			BasicVertex({  0.5f, -0.5f, -offset }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, -1.0f }, { 1.0f, 0.0f }),
			BasicVertex({  0.5f,  0.5f, -offset }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, -1.0f }, { 1.0f, 1.0f })
		);

		IndexContainer indices({ 0, 1, 2, 2, 1, 3, 4, 5, 6, 6, 5, 7});

		return Ref<Mesh>(new Mesh(tag, vertices, indices));
	}

	Ref<Mesh> Mesh::Cube(const std::string& tag)
	{
		BasicVertexContainer vertices(
			// Same X
			BasicVertex({ -0.5f, -0.5f, -0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { -1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f }),
			BasicVertex({ -0.5f, -0.5f,  0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { -1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f }),
			BasicVertex({ -0.5f,  0.5f, -0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { -1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f }),
			BasicVertex({ -0.5f,  0.5f,  0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { -1.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }),

			BasicVertex({  0.5f, -0.5f, -0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }, {  1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f }),
			BasicVertex({  0.5f,  0.5f, -0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }, {  1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f }),
			BasicVertex({  0.5f, -0.5f,  0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }, {  1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f }),
			BasicVertex({  0.5f,  0.5f,  0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }, {  1.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }),

			// Same Y
			BasicVertex({ -0.5f, -0.5f, -0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }, {  0.0f, -1.0f, 0.0f }, { 0.0f, 0.0f }),
			BasicVertex({  0.5f, -0.5f, -0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }, {  0.0f, -1.0f, 0.0f }, { 1.0f, 0.0f }),
			BasicVertex({ -0.5f, -0.5f,  0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }, {  0.0f, -1.0f, 0.0f }, { 0.0f, 1.0f }),
			BasicVertex({  0.5f, -0.5f,  0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }, {  0.0f, -1.0f, 0.0f }, { 1.0f, 1.0f }),

			BasicVertex({ -0.5f,  0.5f, -0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }, {  0.0f,  1.0f, 0.0f }, { 0.0f, 0.0f }),
			BasicVertex({ -0.5f,  0.5f,  0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }, {  0.0f,  1.0f, 0.0f }, { 0.0f, 1.0f }),
			BasicVertex({  0.5f,  0.5f, -0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }, {  0.0f,  1.0f, 0.0f }, { 1.0f, 0.0f }),
			BasicVertex({  0.5f,  0.5f,  0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }, {  0.0f,  1.0f, 0.0f }, { 1.0f, 1.0f }),

			// Same Z
			BasicVertex({ -0.5f, -0.5f, -0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }, {  0.0f, 0.0f, -1.0f }, { 0.0f, 0.0f }),
			BasicVertex({ -0.5f,  0.5f, -0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }, {  0.0f, 0.0f, -1.0f }, { 0.0f, 1.0f }),
			BasicVertex({  0.5f, -0.5f, -0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }, {  0.0f, 0.0f, -1.0f }, { 1.0f, 0.0f }),
			BasicVertex({  0.5f,  0.5f, -0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }, {  0.0f, 0.0f, -1.0f }, { 1.0f, 1.0f }),

			BasicVertex({ -0.5f, -0.5f,  0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }, {  0.0f, 0.0f,  1.0f }, { 0.0f, 0.0f }),
			BasicVertex({  0.5f, -0.5f,  0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }, {  0.0f, 0.0f,  1.0f }, { 1.0f, 0.0f }),
			BasicVertex({ -0.5f,  0.5f,  0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }, {  0.0f, 0.0f,  1.0f }, { 0.0f, 1.0f }),
			BasicVertex({  0.5f,  0.5f,  0.5f }, { 1.0f, 1.0f, 1.0f, 1.0f }, {  0.0f, 0.0f,  1.0f }, { 1.0f, 1.0f })
		);

		IndexContainer indices({
			 0,  1,  2,  2,  1,  3,
			 4,  5,  6,  6,  5,  7,
			 8,  9, 10, 10,  9, 11,
			12, 13, 14, 14, 13, 15,
			16, 17, 18, 18, 17, 19,
			20, 21, 22, 22, 21, 23
		});

		return Ref<Mesh>(new Mesh(tag, vertices, indices));
	}

	Ref<Mesh> Mesh::Triangle(const std::string& tag)
	{
		BasicVertexContainer vertices(
			BasicVertex({ -0.5f, -0.5f,  offset }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f,  1.0f }, { 0.0f, 0.0f }),
			BasicVertex({  0.5f, -0.5f,  offset }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f,  1.0f }, { 1.0f, 0.0f }),
			BasicVertex({  0.0f,  0.5f,  offset }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f,  1.0f }, { 0.5f, 1.0f }),

			BasicVertex({ -0.5f, -0.5f, -offset }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 0.0f }),
			BasicVertex({  0.0f,  0.5f, -offset }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, -1.0f }, { 0.5f, 1.0f }),
			BasicVertex({  0.5f, -0.5f, -offset }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, -1.0f }, { 1.0f, 0.0f })
		);

		IndexContainer indices({ 0, 1, 2, 3, 4, 5 });

		return Ref<Mesh>(new Mesh(tag, vertices, indices));
	}
}