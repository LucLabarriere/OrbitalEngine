#pragma once

#include "VertexArray.h"

namespace Orbital
{
	class OpenGLVertexArray: public VertexArray
	{
	public:
		virtual ~OpenGLVertexArray();

		virtual void bind() const override;
		virtual void unbind() const override;

	protected:
		friend VertexArray;

		OpenGLVertexArray();
	};
}
