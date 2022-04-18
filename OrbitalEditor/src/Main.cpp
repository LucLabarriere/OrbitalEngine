#include "EditorApplication.h"


//class NBatch
//{
//public:
//	NBatch(size_t vertexCount, size_t indexCount = 0)
//		: m_vertices(vertexCount)
//		, m_indices(indexCount == 0 ? int(vertexCount - 2) * 3 : indexCount)
//		, m_freeVertices(m_vertices.getCount(), true)
//		, m_freeIndices(m_indices.getCount(), true)
//	{
//
//	}
//
//	void registerMesh(Components::MeshRenderer& mr, Components::Transform& t)
//	{
//		auto& vertices = mr.Mesh.lock()->getVertices();
//		auto& indices = mr.Mesh.lock()->getIndices();
//
//		if (mr.batched)
//			return;
//
//		// Do transformations to the vertices here
//		auto [vertexPosition, indexPosition] = getAvailableSlot(vertices.getCount(), indices.getCount());
//		
//		if (vertexPosition == -1 || indexPosition == -1)
//		{
//			std::cout << "Error not enough available space, Vertex:" << vertexPosition << " Index:" << indexPosition << std::endl;
//			return;
//		}
//
//		mr.vertexPosition = vertexPosition;
//		mr.indexPosition = indexPosition;
//		mr.batched = true;
//
//		for (size_t i = vertexPosition; i < vertices.getCount() + vertexPosition; i++)
//		{
//			m_vertices[i] = BasicVertex(vertices[i - vertexPosition]);
//			m_freeVertices[i] = false;
//		}
//
//		for (size_t i = indexPosition; i < indices.getCount() + indexPosition; i++)
//		{
//			m_indices[i] = vertexPosition;
//			m_freeIndices[i] = false;
//		}
//	}
//
//	void deleteMesh(Components::MeshRenderer& meshRenderer)
//	{
//		size_t vertexPosition = meshRenderer.vertexPosition;
//		size_t indexPosition = meshRenderer.indexPosition;
//		auto& vertices = meshRenderer.Mesh.lock()->getVertices();
//		auto& indices = meshRenderer.Mesh.lock()->getIndices();
//
//		for (size_t i = vertexPosition; i < vertices.getCount() + vertexPosition; i++)
//		{
//			m_freeVertices[i] = true;
//		}
//
//		for (size_t i = indexPosition; i < indices.getCount() + indexPosition; i++)
//		{
//			m_freeIndices[i] = true;
//		}
//
//		meshRenderer.batched = false;
//		meshRenderer.vertexPosition = -1;
//		meshRenderer.indexPosition = -1;
//	}
//
//	std::array<int, 2> getAvailableSlot(size_t vertexCount, size_t indexCount)
//	{
//		size_t availableVertices = 0;
//		size_t emptyVertices = 0;
//		size_t availableIndices = 0;
//		size_t emptyIndices = 0;
//
//		int vertexPosition = -1;
//		int indexPosition = -1;
//
//		// Vertices
//		for (int i = 0; i < m_freeVertices.size(); i++)
//		{
//			if (availableVertices == vertexCount)
//			{
//				vertexPosition = i - vertexCount;
//				break;
//			}
//			else if (m_freeVertices[i])
//			{
//				availableVertices += 1;
//				emptyVertices += 1;
//			}
//			else
//			{
//				availableVertices = 0;
//			}
//		}
//
//		// Indices
//		for (int i = 0; i < m_freeIndices.size(); i++)
//		{
//			if (availableIndices == indexCount)
//			{
//				indexPosition = i - indexCount;
//				break;
//			}
//			else if (m_freeIndices[i])
//			{
//				availableIndices += 1;
//				emptyIndices += 1;
//			}
//			else
//			{
//				availableIndices = 0;
//			}
//		}
//
//		// No Slot available
//		if (emptyVertices > 50 || emptyIndices > 50)
//			std::cout << "The batch is holed, remake it from scratch" << std::endl;
//
//		return { vertexPosition, indexPosition };
//	}
//	
//	void printVertices()
//	{
//		for (size_t i = 0; i < m_vertices.getCount(); i++)
//		{
//			const auto& pos = m_vertices[i].position;
//			std::cout << i;
//
//			if (!m_freeVertices[i])
//				std::cout << ": " << pos[0] << ", " << pos[1] << ", " << pos[2];
//
//			std::cout << "\n";
//		}
//	}
//
//	void printIndices()
//	{
//		for (size_t i = 0; i < m_indices.getCount(); i++)
//		{
//			const auto& val = m_indices[i];
//			std::cout << i;
//
//			if (!m_freeIndices[i])
//				std::cout << ": " << val;
//
//			std::cout << "\n";
//		}
//	}
//
//private:
//	BasicVertexContainer m_vertices;
//	IndexContainer m_indices;
//
//	std::vector<bool> m_freeVertices;
//	std::vector<bool> m_freeIndices;
//};

int main()
{
	EditorApplication app;
	app.run();
	return 0;
}