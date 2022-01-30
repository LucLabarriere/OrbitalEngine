#pragma once

namespace OrbitalEngine
{
	class Application;

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
			friend Application;

			unsigned int m_rendererId;
	};

}
