#pragma once

#include "OrbitalEngine/Graphics/Vertices.h"
#include "OrbitalEngine/Graphics/IndexContainer.h"

namespace Orbital
{
	class MeshManager;

	class Mesh : public Asset
	{
	public:
		const BasicVertexContainer& GetVertices() const { return mVertices; }
		const IndexContainer& getIndices() const { return mIndices; }

	private:
		Mesh(const std::string& tag, const BasicVertexContainer& vertices, const IndexContainer& indices);

		static Ref<Mesh> Quad(const std::string& tag = "Quad");
		static Ref<Mesh> Cube(const std::string& tag = "Cube");
		static Ref<Mesh> Triangle(const std::string& tag = "Triangle");

	private:
		friend MeshManager;

		BasicVertexContainer mVertices;
		IndexContainer mIndices;

		static inline size_t sId = 0;
	};
}