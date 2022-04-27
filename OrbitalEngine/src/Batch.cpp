#include "OrbitalEngine/Graphics/Batch.h"
#include "OrbitalEngine/Components.h"
#include "OrbitalEngine/Utils.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include <span>

namespace Orbital
{
	Batch::Batch(WeakRef<Material>& material, size_t vertexCount, size_t indexCount)
		: m_material(material)
		, m_vertices(vertexCount)
		, m_indices(indexCount == 0 ? int(vertexCount - 2) * 3 : indexCount)
		, m_freeVertices(m_vertices.getCount(), true)
		, m_modifiedVertices(m_vertices.getCount(), false)
		, m_freeIndices(m_indices.getCount(), true)
		, m_modifiedIndices(m_indices.getCount(), false)
		, m_renderMode(OE_DYNAMIC_DRAW)
	{
		m_vao = Ref<VertexArray>(VertexArray::Create());
		m_vbo = Ref<VertexBuffer>(VertexBuffer::Create(m_renderMode));
		m_ibo = Ref<IndexBuffer>(IndexBuffer::Create(m_renderMode));
	}

	void Batch::bind() const
	{
		m_vao->bind();
		m_ibo->bind();
	}

	void Batch::bindMaterial() const
	{
		m_material.lock()->bind();
	}

	void Batch::allocateMemory() const
	{
		m_vao->bind();
		m_vbo->bind();
		m_vbo->allocateMemory(nullptr, m_vertices.getSize());

		m_ibo->bind();
		m_ibo->allocateMemory(nullptr, m_indices.getSize());

		m_vertices.setLayout(*m_vbo);
	}

	void Batch::submitData() const
	{
		m_vao->bind();
		m_vbo->bind();
		// Do submitSubData Here
		m_vbo->submitData(m_vertices.getData(), m_vertices.getSize());

		m_ibo->bind();
		m_ibo->submitData(m_indices.getData(), m_indices.getSize());
	}

	void Batch::render()
	{
		m_vao->bind();
		m_vbo->bind();

		for (auto& subData : m_subDataVertices)
		{
			size_t stride = (subData.lastIndex - subData.firstIndex + 1);
			m_vbo->submitSubData(
				m_vertices.getFirstVertex() + subData.firstIndex,
				subData.firstIndex * sizeof(BasicVertex),
				stride * sizeof(BasicVertex)
			);
		}

		m_currentSubDataVertices = nullptr;
		m_subDataVertices.resize(0);

		m_ibo->bind();
		
		for (auto& subData : m_subDataIndices)
		{
			size_t stride = (subData.lastIndex - subData.firstIndex + 1);
			m_ibo->submitSubData(
				m_indices.getFirstIndex() + subData.firstIndex,
				subData.firstIndex * sizeof(unsigned int),
				stride * sizeof(unsigned int));
		}
		m_currentSubDataIndices = nullptr;
		m_subDataIndices.resize(0);

		RenderCommands::DrawIndexed(OE_TRIANGLES, m_indices.getSize());
		Metrics::IncrementBatchCount();
	}

	void Batch::registerMesh(Components::MeshRenderer& mr, Components::Transform& t)
	{
		auto& vertices = mr.Mesh.lock()->getVertices();
		auto& indices = mr.Mesh.lock()->getIndices();

		if (!t.isDirty())
			return;

		int vertexPointer = mr.vertexPointer;
		int indexPointer = mr.indexPointer;

		if (vertexPointer == -1 || indexPointer == -1)
		{
			std::tie(vertexPointer, indexPointer) = getAvailableSlot(vertices.getCount(), indices.getCount());
		}

		if (vertexPointer == -1 || indexPointer == -1)
		{
			Logger::Error("Error not enough available space, Vertex: {} Index: {}", vertexPointer, indexPointer);
			return;
		}

		mr.vertexPointer = vertexPointer;
		mr.indexPointer = indexPointer;
		mr.Batch = shared_from_this();

		glm::mat4 model(1.0f);
		model = glm::translate(model, t.Position());
		model = glm::rotate(model, glm::radians(t.Rotation()[0]), { 1.0f, 0.0f, 0.0f });
		model = glm::rotate(model, glm::radians(t.Rotation()[1]), { 0.0f, 1.0f, 0.0f });
		model = glm::rotate(model, glm::radians(t.Rotation()[2]), { 0.0f, 0.0f, 1.0f });
		model = glm::scale(model, t.Scale());

		glm::mat4 rotation(0.0f);
		rotation = glm::rotate(rotation, glm::radians(t.Rotation()[0]), { 1.0f, 0.0f, 0.0f });
		rotation = glm::rotate(rotation, glm::radians(t.Rotation()[1]), { 0.0f, 1.0f, 0.0f });
		rotation = glm::rotate(rotation, glm::radians(t.Rotation()[2]), { 0.0f, 0.0f, 1.0f });
		
		if (m_currentSubDataVertices == nullptr || m_currentSubDataVertices->lastIndex + 1 != vertexPointer)
		{
			m_subDataVertices.push_back(BufferSubData(vertexPointer, vertexPointer + vertices.getCount() - 1));
			m_currentSubDataVertices = &m_subDataVertices[m_subDataVertices.size() - 1];
		}
		else
		{
			m_currentSubDataVertices->lastIndex += vertices.getCount();
		}

		for (size_t i = 0; i < vertices.getCount(); i++)
		{
			m_vertices[i + vertexPointer] = vertices[i];
			m_vertices[i + vertexPointer].position = model * Vec4(m_vertices[i + vertexPointer].position, 1.0f);
			m_vertices[i + vertexPointer].normal = Mat3(glm::transpose(glm::inverse(model))) * m_vertices[i + vertexPointer].normal;
			m_freeVertices[i + vertexPointer] = false;
			m_modifiedVertices[i + vertexPointer] = true;
		}

		if (m_currentSubDataIndices == nullptr || m_currentSubDataIndices->lastIndex  + 1 != indexPointer)
		{
			m_subDataIndices.push_back(BufferSubData(indexPointer, indexPointer + indices.getCount() - 1));
			m_currentSubDataIndices = &m_subDataIndices[m_subDataIndices.size() - 1];
		}
		else
		{
			m_currentSubDataIndices->lastIndex += indices.getCount();
		}

		for (size_t i = 0; i < indices.getCount(); i++)
		{
			m_indices[i + indexPointer] = vertexPointer + indices[i];
			m_freeIndices[i + indexPointer] = false;
			m_modifiedIndices[i + indexPointer] = true;
		}

		updateFullStatus();

		t.cleanUp();
	}


	void Batch::deleteMesh(Components::MeshRenderer& mr)
	{
		size_t vertexPointer = mr.vertexPointer;
		size_t indexPointer = mr.indexPointer;

		auto& vertices = mr.Mesh.lock()->getVertices();
		auto& indices = mr.Mesh.lock()->getIndices();

		for (size_t i = vertexPointer; i < vertices.getCount() + vertexPointer; i++)
		{
			m_vertices[i] = BasicVertex::Empty();
			m_freeVertices[i] = true;
			m_modifiedVertices[i] = true;
		}

		for (size_t i = indexPointer; i < indices.getCount() + indexPointer; i++)
		{
			m_indices[i] = 0;
			m_freeIndices[i] = true;
			m_modifiedIndices[i] = true;
		}

		mr.Batch = nullptr;
		mr.vertexPointer = -1;
		mr.indexPointer = -1;

		updateFullStatus();
	}

	bool Batch::meshFits(Components::MeshRenderer& mr)
	{
		auto& vertices = mr.Mesh.lock()->getVertices();
		auto& indices = mr.Mesh.lock()->getIndices();

		auto [vertexPointer, indexPointer] = getAvailableSlot(vertices.getCount(), indices.getCount());

		if (vertexPointer != -1 && indexPointer != -1)
			return true;

		return false;
	}

	std::tuple<int, int> Batch::getAvailableSlot(size_t vertexCount, size_t indexCount)
	{
		size_t availableVertices = 0;
		size_t emptyVertices = 0;
		size_t availableIndices = 0;
		size_t emptyIndices = 0;

		int vertexPointer = -1;
		int indexPointer = -1;

		// Vertices
		for (int i = 0; i < m_freeVertices.size(); i++)
		{
			if (availableVertices == vertexCount)
			{
				vertexPointer = i - vertexCount;
				break;
			}
			else if (m_freeVertices[i])
			{
				availableVertices += 1;
				emptyVertices += 1;
			}
			else
			{
				availableVertices = 0;
			}
		}

		// Indices
		for (int i = 0; i < m_freeIndices.size(); i++)
		{
			if (availableIndices == indexCount)
			{
				indexPointer = i - indexCount;
				break;
			}
			else if (m_freeIndices[i])
			{
				availableIndices += 1;
				emptyIndices += 1;
			}
			else
			{
				availableIndices = 0;
			}
		}

		if (emptyVertices > 50 || emptyIndices > 50)
			OE_RAISE_SIGSEGV("The batch is holed, remake it from scratch");

		return std::make_tuple(vertexPointer, indexPointer);
	}

	void Batch::updateFullStatus()
	{
		auto [ vertexPointer, indexPointer ] = getAvailableSlot(24, 36);

		if (vertexPointer == -1 || indexPointer == -1)
			m_full = true;
		else
			m_full = false;
	}
}