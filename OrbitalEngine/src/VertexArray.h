#pragma once

namespace OrbitalEngine
{
	class Batch;

	class VertexArray
	{
	public:
		virtual ~VertexArray() { }

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

	protected:
		VertexArray() : m_rendererId(0) { }
		static VertexArray* Create();

	protected:
			friend Batch;

			unsigned int m_rendererId;
	};

}
