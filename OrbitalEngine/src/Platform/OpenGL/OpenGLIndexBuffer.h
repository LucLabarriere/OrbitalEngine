#pragma once

#include "IndexBuffer.h"

namespace OrbitalEngine
{
	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		virtual ~OpenGLIndexBuffer() override;
		
		virtual void bind() const override;
		virtual void unbind() const override;

		virtual void allocateMemory(const void* data, size_t size) const override;
		virtual void submitData(const void* data, size_t size) const override;

	private:
		OpenGLIndexBuffer(unsigned int drawMode);

	private:
		friend IndexBuffer;
	};
}