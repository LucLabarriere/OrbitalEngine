#include "OpenGLVertexArray.h"

namespace Orbital
{
	VertexArray* VertexArray::Create()
	{
		return new OpenGLVertexArray();
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glad_glDeleteVertexArrays(1, &mRendererId);
	}

	void OpenGLVertexArray::Bind() const
	{
		glad_glBindVertexArray(mRendererId);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glad_glBindVertexArray(0);
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glad_glGenVertexArrays(1, &mRendererId);
	}
}