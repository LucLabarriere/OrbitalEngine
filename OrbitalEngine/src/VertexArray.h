#pragma once

namespace Orbital
{
	class VertexArray
	{
	public:
		static VertexArray* Create();
		virtual ~VertexArray() { }

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

	protected:
		VertexArray() : mRendererId(0) { }

	protected:
			unsigned int mRendererId;
	};

}
