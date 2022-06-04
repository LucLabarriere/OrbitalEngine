#pragma once

#include "IndexBuffer.h"

namespace Orbital
{
	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		virtual ~OpenGLIndexBuffer() override;
		
		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AllocateMemory(const void* data, size_t size) const override;
		virtual void SubmitData(const void* data, size_t size) const override;
		virtual void submitSubData(const void* data, size_t offset, size_t size) const override;

	private:
		OpenGLIndexBuffer(unsigned int drawMode);

	private:
		friend IndexBuffer;
	};
}