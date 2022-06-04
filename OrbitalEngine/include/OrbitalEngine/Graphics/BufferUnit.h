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

		void SetModelMatrixUniform(WeakRef<Shader> shader, const Transform& t);
		bool operator==(const BufferUnit& otherUnit);
		void Bind() const;
		size_t GetId() const { return mId; }
		WeakRef<Mesh> GetMesh() const { return mMesh; }
		WeakRef<Material> GetMaterial() const { return mMaterial; }

	private:
		size_t mId;
		WeakRef<Mesh> mMesh;
		WeakRef<Material> mMaterial;
		Ref<VertexArray> mVao;
		Ref<VertexBuffer> mVbo;
		Ref<IndexBuffer> mIbo;

	};
}
