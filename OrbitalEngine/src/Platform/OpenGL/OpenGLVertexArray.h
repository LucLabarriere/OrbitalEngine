#pragma once

#include "VertexArray.h"

namespace Orbital
{
	class OpenGLVertexArray: public VertexArray
	{
	public:
		virtual ~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void Unbind() const override;

	protected:
		friend VertexArray;

		OpenGLVertexArray();
	};
}
