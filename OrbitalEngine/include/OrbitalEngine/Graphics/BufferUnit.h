#pragma once

#include "OrbitalEngine/Utils.h"

namespace Orbital
{
	class Transform;
	class Material;
	class Shader;
	class Mesh;
	class VertexArray;
	class VertexBuffer;
	class IndexBuffer;

	class BufferUnit
	{
	public:
		BufferUnit(WeakRef<Mesh> mesh, WeakRef<Material> material);

		void setModelMatrixUniform(WeakRef<Shader> shader, const Transform& t);
		bool operator==(const BufferUnit& otherUnit);
		void bind() const;
		size_t getId() const { return m_id; }
		WeakRef<Mesh> getMesh() const { return m_mesh; }
		WeakRef<Material> getMaterial() const { return m_material; }

	private:
		size_t m_id;
		WeakRef<Mesh> m_mesh;
		WeakRef<Material> m_material;
		Ref<VertexArray> m_vao;
		Ref<VertexBuffer> m_vbo;
		Ref<IndexBuffer> m_ibo;

	};
}
