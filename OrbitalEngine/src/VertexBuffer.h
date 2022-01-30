#pragma once

#include "OrbitalEngine/Vertices.h"

namespace OrbitalEngine
{
	class Application;

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {};

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void allocateMemory(const void* data, unsigned int size) const = 0;
		virtual void setAttribute(unsigned int index, unsigned int count, unsigned int type,
			unsigned int normalized, unsigned int size, const void* pointer) const = 0;

	protected:
		VertexBuffer(unsigned int drawMode)
			: m_rendererId(0), m_drawMode(drawMode) { }
		static VertexBuffer* Create(unsigned int drawMode);

	protected:
		friend Application;

		unsigned int m_rendererId;
		unsigned int m_drawMode;
	};
}
