#pragma once

namespace Orbital
{
	class VertexArray
	{
	public:
		static VertexArray* Create();
		virtual ~VertexArray() { }

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

	protected:
		VertexArray() : m_rendererId(0) { }

	protected:
			unsigned int m_rendererId;
	};

}
