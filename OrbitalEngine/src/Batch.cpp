#include "OrbitalEngine/Graphics/Batch.h"
#include "OrbitalEngine/Components.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace Orbital
{
	Batch::Batch(RenderMode renderMode, size_t count, size_t indexCount)
		: m_maxVertexContainerCount(count)
		, m_maxIndexContainerCount(indexCount == 0 ? count * 3 : indexCount)
		, m_maxVertexContainerSize(count * sizeof(BasicVertex))
		, m_maxIndexContainerSize(count * sizeof(unsigned int) * 3)
		, m_renderMode(renderMode)
		, m_vertices(count)
		, m_indices(m_maxIndexContainerCount)
		, m_vao(nullptr) , m_vbo(nullptr), m_ibo(nullptr)
	{
		unsigned drawMode;
		if (renderMode == RenderMode::STATIC_BATCHED || renderMode == RenderMode::STATIC_NOT_BATCHED)
		{
			drawMode = OE_STATIC_DRAW;
		}
		else if (renderMode == RenderMode::DYNAMIC_BATCHED || renderMode == RenderMode::DYNAMIC_NOT_BATCHED)
		{
			drawMode = OE_DYNAMIC_DRAW;
		}

		m_vao = Ref<VertexArray>(VertexArray::Create());
		m_vbo = Ref<VertexBuffer>(VertexBuffer::Create(drawMode));
		m_ibo = Ref<IndexBuffer>(IndexBuffer::Create(drawMode));
	}

	void Batch::bind() const
	{
		m_vao->bind();
		m_ibo->bind();
	}

	void Batch::allocateMemory() const
	{
		const void* vertexData = m_vertices.getData();
		const void* indexData = m_indices.getData();

		size_t vertexContainerSize = m_maxVertexContainerSize;
		size_t indexContainerSize = m_maxIndexContainerSize;

		m_vao->bind();
		m_vbo->bind();
		m_vbo->allocateMemory(vertexData, vertexContainerSize);

		m_ibo->bind();
		m_ibo->allocateMemory(indexData, indexContainerSize);

		m_vertices.setLayout(*m_vbo);
	}

	void Batch::submitData() const
	{
		m_vao->bind();
		m_vbo->bind();
		m_vbo->submitData(m_vertices.getData(), getVertexContainerSize());

		m_ibo->bind();
		m_ibo->submitData(m_indices.getData(), getIndexContainerSize());
	}

	void Batch::requestDraw(bool request)
	{
		m_requestDraw = request;
	}

	void Batch::requestFlush(bool request)
	{
		m_requestFlush = request;
	}

	void Batch::flush()
	{
		m_currentVertex = 0;
		m_currentIndex = 0;
		m_requestFlush = false;
	}

	void Batch::addMesh(const std::string& meshTag, const Components::Transform& transform)
	{
		addMesh(MeshManager::Get(meshTag), transform);
	}

	void Batch::addMesh(const WeakRef<Mesh>& meshWeak, const Components::Transform& transform)
	{
		auto mesh = meshWeak.lock();
		const auto& vertices = mesh->getVertices();
		const auto& indices = mesh->getIndices();
		const std::string& tag = mesh->getTag();
		size_t count = vertices.getCount();
		size_t available = getAvailableVertexCount();

		OE_ASSERT(
			count <= available,
			"Batch: {} needs {} vertices but only {} are available",
			tag, count, available
		);

		for (size_t i = 0; i < indices.getCount(); i++)
		{
			m_indices[m_currentIndex + i] = m_currentVertex + indices[i];
		}

		m_currentIndex += indices.getCount();
		glm::mat4 model(1.0f);
		model = glm::translate(model, transform.Position());
		model = glm::rotate(model, glm::radians(transform.Rotation()[0]), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(transform.Rotation()[1]), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(transform.Rotation()[2]), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, transform.Scale());

		glm::mat4 rotation(0.0f);
		rotation = glm::rotate(rotation, glm::radians(transform.Rotation()[0]), glm::vec3(1.0f, 0.0f, 0.0f));
		rotation = glm::rotate(rotation, glm::radians(transform.Rotation()[1]), glm::vec3(0.0f, 1.0f, 0.0f));
		rotation = glm::rotate(rotation, glm::radians(transform.Rotation()[2]), glm::vec3(0.0f, 0.0f, 1.0f));

		for (size_t i = 0; i < vertices.getCount(); i++)
		{
			m_vertices[m_currentVertex + i] = vertices[i];
			m_vertices[m_currentVertex + i].position = model * glm::vec4(m_vertices[m_currentVertex + i].position, 1.0f);
			m_vertices[m_currentVertex + i].normal = glm::mat3(glm::transpose(glm::inverse(model))) * m_vertices[m_currentVertex + i].normal;
		}

		m_currentVertex += vertices.getCount();
	}

	size_t Batch::getVertexContainerCount() const
	{
		return m_currentVertex;
	}

	size_t Batch::getVertexContainerSize() const
	{
		return getVertexContainerCount() * sizeof(BasicVertex);
	}

	size_t Batch::getIndexContainerCount() const
	{
		return m_currentIndex;
	}

	size_t Batch::getIndexContainerSize() const
	{
		return getIndexContainerCount() * sizeof(unsigned int);
	}

	size_t Batch::getAvailableVertexCount() const
	{
		return m_vertices.getCount() - m_currentVertex;
	}

	size_t Batch::getAvailableIndexCount() const
	{
		return m_indices.getCount() - m_currentIndex;
	}
}