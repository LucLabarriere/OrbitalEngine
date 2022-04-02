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
		glad_glGenBuffers(1, &m_rendererId);
		bind();
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glad_glDeleteBuffers(1, &m_rendererId);
	}

	void OpenGLIndexBuffer::bind() const
	{
		glad_glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererId);
	}

	void OpenGLIndexBuffer::unbind() const
	{
		glad_glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void OpenGLIndexBuffer::allocateMemory(const void* data, size_t size) const
	{
		glad_glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, m_drawMode);
	}

	void OpenGLIndexBuffer::submitData(const void* data, size_t size) const
	{
		glad_glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, size, data);
	}
}