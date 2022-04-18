#pragma once

#include "VertexBuffer.h"

namespace Orbital
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		virtual ~OpenGLVertexBuffer() override;

		virtual void bind() const override;
		virtual void unbind() const override;

		virtual void allocateMemory(const void* data, size_t size) const override;
		virtual void submitData(const void* data, size_t size) const override;
		virtual void submitSubData(const void* data, size_t offset, size_t size) const override;
		virtual void setAttribute(size_t index, size_t count, unsigned int type,
			unsigned int normalized, size_t size, const void* pointer) const override;

	private:
		OpenGLVertexBuffer(unsigned int drawMode);

		friend VertexBuffer;
	};
}
