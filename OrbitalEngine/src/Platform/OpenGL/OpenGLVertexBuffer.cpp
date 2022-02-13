#include "OpenGLVertexBuffer.h"


namespace OrbitalEngine
{
	VertexBuffer* VertexBuffer::Create(unsigned int drawMode)
	{
		return new OpenGLVertexBuffer(drawMode);
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(unsigned int drawMode)
		: VertexBuffer(drawMode)
	{
 		glad_glGenBuffers(1, &m_rendererId);
		bind();
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glad_glDeleteBuffers(1, &m_rendererId);
	}

	void OpenGLVertexBuffer::bind() const
	{
		glad_glBindBuffer(GL_ARRAY_BUFFER, m_rendererId);
	}

	void OpenGLVertexBuffer::unbind() const
	{
		glad_glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void OpenGLVertexBuffer::allocateMemory(const void* data, size_t size) const
	{
		glad_glBufferData(GL_ARRAY_BUFFER, size, data, m_drawMode);
	}

	void OpenGLVertexBuffer::submitData(const void* data, size_t size) const
	{
		glad_glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	}

	void OpenGLVertexBuffer::setAttribute(size_t index, size_t count, unsigned int type,
		unsigned int normalized, size_t size, const void* pointer) const
	{
		glad_glEnableVertexAttribArray((GLuint)index);
		glad_glVertexAttribPointer(
			(GLuint)index,
			(GLint)count,
			type,
			normalized,
			(GLsizei)size,
			pointer
		);
	}


}
