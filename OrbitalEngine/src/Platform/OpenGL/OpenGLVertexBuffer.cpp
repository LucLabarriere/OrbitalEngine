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

	}

	void OpenGLVertexBuffer::bind() const
	{
		glad_glBindBuffer(GL_ARRAY_BUFFER, m_rendererId);
	}

	void OpenGLVertexBuffer::unbind() const
	{
		glad_glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void OpenGLVertexBuffer::allocateMemory(const void* data, unsigned int size) const
	{
		glad_glBufferData(GL_ARRAY_BUFFER, size, data, m_drawMode);
	}

	void OpenGLVertexBuffer::setAttribute(unsigned int index, unsigned int count, unsigned int type,
		unsigned int normalized, unsigned int size, const void* pointer) const
	{
		glad_glEnableVertexAttribArray(index);
		glad_glVertexAttribPointer(
			index,
			count,
			type,
			normalized,
			size,
			pointer
		);
	}


}
