#include "OrbitalEngine/Graphics.h"
#include "OrbitalEngine/Components/Transform.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"

namespace Orbital
{
	BufferUnit::BufferUnit(WeakRef<Mesh> mesh, WeakRef<Material> material)
		: m_mesh(mesh)
		, m_material(material)
	{
		m_vao = Ref<VertexArray>(VertexArray::Create());
		m_vbo = Ref<VertexBuffer>(VertexBuffer::Create(OE_STATIC_DRAW));
		m_ibo = Ref<IndexBuffer>(IndexBuffer::Create(OE_STATIC_DRAW));

		auto m = mesh.lock();
		m_id = m->getId();
		auto& vertices = m->getVertices();
		auto& indices = m->getIndices();

		m_vao->bind();
		m_vbo->bind();
		m_vbo->allocateMemory(nullptr, vertices.getSize());
		m_vbo->submitData(vertices.getData(), vertices.getSize());

		m_ibo->bind();
		m_ibo->allocateMemory(nullptr, indices.getSize());
		m_ibo->submitData(indices.getData(), indices.getSize());

		m->getVertices().setLayout(*m_vbo);
	}

	void BufferUnit::setModelMatrixUniform(WeakRef<Shader> shader, const Transform& t)
	{
		Mat4 model(1.0f);
		model = glm::translate(model, t.Position());
		model = glm::rotate(model, glm::radians(t.Rotation()[0]), { 1.0f, 0.0f, 0.0f });
		model = glm::rotate(model, glm::radians(t.Rotation()[1]), { 0.0f, 1.0f, 0.0f });
		model = glm::rotate(model, glm::radians(t.Rotation()[2]), { 0.0f, 0.0f, 1.0f });
		model = glm::scale(model, t.Scale());

		shader.lock()->setUniformMat4f("u_MMatrix", model);
	}

	bool BufferUnit::operator==(const BufferUnit& otherUnit)
	{
		return otherUnit.getId() == getId();
	}

	void BufferUnit::bind() const
	{
		m_vao->bind();
		m_ibo->bind();
	}
}