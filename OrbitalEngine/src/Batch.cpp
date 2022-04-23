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
		, m_modifiedVertices(m_vertices.getCount(), true)
		, m_freeIndices(m_indices.getCount(), true)
		, m_modifiedIndices(m_indices.getCount(), true)
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

	void Batch::render() const
	{
		size_t stride = 0;
		size_t offset = 0;
		bool recording = true;

		for (size_t i = 0; i < m_modifiedVertices.size(); i++)
		{
			if (m_modifiedVertices[i])
			{
				if (!recording)
				{
					recording = true;
					offset = i;
				}
				else
				{
					stride += 1;
				}
			}
			else if (recording)
			{
				recording = false;
				m_vbo->submitSubData(m_vertices.getData(), offset * sizeof(BasicVertex), stride * sizeof(BasicVertex));
				stride = 0;
			}
		}

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

		for (size_t i = 0; i < vertices.getCount(); i++)
		{
			m_vertices[i + vertexPointer] = vertices[i];
			m_vertices[i + vertexPointer].position = model * Vec4(m_vertices[i + vertexPointer].position, 1.0f);
			m_vertices[i + vertexPointer].normal = Mat3(glm::transpose(glm::inverse(model))) * m_vertices[i + vertexPointer].normal;
			m_freeVertices[i + vertexPointer] = false;
			m_modifiedVertices[i + vertexPointer] = true;
		}

		for (size_t i = indexPointer; i < indices.getCount() + indexPointer; i++)
		{
			m_indices[i] = vertexPointer + indices[i - indexPointer];
			m_freeIndices[i] = false;
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