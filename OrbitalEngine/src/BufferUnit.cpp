#include "OrbitalEngine/Graphics.h"
#include "OrbitalEngine/Components/Transform.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"

namespace Orbital
{
	BufferUnit::BufferUnit(WeakRef<Mesh> mesh, WeakRef<Material> material)
		: mMesh(mesh)
		, mMaterial(material)
	{
		mVao = Ref<VertexArray>(VertexArray::Create());
		mVbo = Ref<VertexBuffer>(VertexBuffer::Create(OE_STATIC_DRAW));
		mIbo = Ref<IndexBuffer>(IndexBuffer::Create(OE_STATIC_DRAW));

		auto m = mesh.lock();
		mId = m->GetId();
		auto& vertices = m->GetVertices();
		auto& indices = m->getIndices();

		mVao->Bind();
		mVbo->Bind();
		mVbo->AllocateMemory(nullptr, vertices.GetSize());
		mVbo->SubmitData(vertices.GetData(), vertices.GetSize());

		mIbo->Bind();
		mIbo->AllocateMemory(nullptr, indices.GetSize());
		mIbo->SubmitData(indices.GetData(), indices.GetSize());

		m->GetVertices().SetLayout(*mVbo);
	}

	void BufferUnit::SetModelMatrixUniform(WeakRef<Shader> shader, const Transform& t)
	{
		Mat4 model(1.0f);
		model = glm::translate(model, t.GetPosition());
		model = glm::rotate(model, glm::radians(t.GetRotation()[0]), { 1.0f, 0.0f, 0.0f });
		model = glm::rotate(model, glm::radians(t.GetRotation()[1]), { 0.0f, 1.0f, 0.0f });
		model = glm::rotate(model, glm::radians(t.GetRotation()[2]), { 0.0f, 0.0f, 1.0f });
		model = glm::scale(model, t.GetScale());

		shader.lock()->SetUniformMat4f("u_MMatrix", model);
	}

	bool BufferUnit::operator==(const BufferUnit& otherUnit)
	{
		return otherUnit.GetId() == GetId();
	}

	void BufferUnit::Bind() const
	{
		mVao->Bind();
		mIbo->Bind();
	}
}