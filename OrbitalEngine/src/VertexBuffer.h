#pragma once

#include "OrbitalEngine/Graphics/Vertices.h"

namespace Orbital
{
	class VertexBuffer
	{
	public:
		static VertexBuffer* Create(unsigned int drawMode);
		virtual ~VertexBuffer() {};

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AllocateMemory(const void* data, size_t size) const = 0;
		virtual void SubmitData(const void* data, size_t size) const = 0;
		virtual void submitSubData(const void* data, size_t offset, size_t size) const = 0;
		virtual void setAttribute(size_t index, size_t count, unsigned int type,
			unsigned int normalized, size_t size, const void* pointer) const = 0;

	protected:
		VertexBuffer(unsigned int drawMode)
			: mRendererId(0), mDrawMode(drawMode) { }

	protected:
		unsigned int mRendererId;
		unsigned int mDrawMode;
	};
}
