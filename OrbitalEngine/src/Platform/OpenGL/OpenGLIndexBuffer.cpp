#include "OpenGLIndexBuffer.h"

namespace Orbital
{
	IndexBuffer* IndexBuffer::Create(unsigned int drawMode)
	{
		return new OpenGLIndexBuffer(drawMode);
	}

	OpenGLIndexBuffer::OpenGLIndexBuffer(unsigned int drawMode)
		: IndexBuffer(drawMode)
	{
		glad_glGenBuffers(1, &mRendererId);
		Bind();
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glad_glDeleteBuffers(1, &mRendererId);
	}

	void OpenGLIndexBuffer::Bind() const
	{
		glad_glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRendererId);
	}

	void OpenGLIndexBuffer::Unbind() const
	{
		glad_glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void OpenGLIndexBuffer::AllocateMemory(const void* data, size_t size) const
	{
		glad_glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, mDrawMode);
	}

	void OpenGLIndexBuffer::SubmitData(const void* data, size_t size) const
	{
		glad_glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, size, data);
	}

	void OpenGLIndexBuffer::submitSubData(const void* data, size_t offset, size_t size) const
	{
		glad_glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data);
	}
}