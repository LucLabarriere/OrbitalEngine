#pragma once

#include "VertexBuffer.h"

namespace OrbitalEngine
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(unsigned int drawMode);
		virtual ~OpenGLVertexBuffer() override;

		virtual void bind() const override;
		virtual void unbind() const override;
		virtual void allocateMemory(const void* data, unsigned int size) const override;
		virtual void setAttribute(unsigned int index, unsigned int count, unsigned int type,
			unsigned int normalized, unsigned int size, const void* pointer) const override;

	private:
		friend VertexBuffer;
	};
}
