#include "OpenGLVertexBuffer.h"


namespace Orbital
{
	VertexBuffer* VertexBuffer::Create(unsigned int drawMode)
	{
		return new OpenGLVertexBuffer(drawMode);
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(unsigned int drawMode)
		: VertexBuffer(drawMode)
	{
 		glad_glGenBuffers(1, &mRendererId);
		Bind();
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glad_glDeleteBuffers(1, &mRendererId);
	}

	void OpenGLVertexBuffer::Bind() const
	{
		glad_glBindBuffer(GL_ARRAY_BUFFER, mRendererId);
	}

	void OpenGLVertexBuffer::Unbind() const
	{
		glad_glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void OpenGLVertexBuffer::AllocateMemory(const void* data, size_t size) const
	{
		glad_glBufferData(GL_ARRAY_BUFFER, size, data, mDrawMode);
	}

	void OpenGLVertexBuffer::SubmitData(const void* data, size_t size) const
	{
		glad_glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	}

	void OpenGLVertexBuffer::submitSubData(const void* data, size_t offset, size_t size) const
	{
		glad_glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
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
