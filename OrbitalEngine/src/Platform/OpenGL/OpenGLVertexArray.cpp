#include "OpenGLVertexArray.h"

namespace OrbitalEngine
{
	VertexArray* VertexArray::Create()
	{
		return new OpenGLVertexArray();
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glad_glDeleteVertexArrays(1, &m_rendererId);
	}

	void OpenGLVertexArray::bind() const
	{
		glad_glBindVertexArray(m_rendererId);
	}

	void OpenGLVertexArray::unbind() const
	{
		glad_glBindVertexArray(0);
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glad_glGenVertexArrays(1, &m_rendererId);
	}
}