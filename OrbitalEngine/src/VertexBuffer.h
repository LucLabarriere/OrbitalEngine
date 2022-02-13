#pragma once

#include "OrbitalEngine/Vertices.h"

namespace OrbitalEngine
{
	class Batch;

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {};

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void allocateMemory(const void* data, size_t size) const = 0;
		virtual void submitData(const void* data, size_t size) const = 0;
		virtual void setAttribute(size_t index, size_t count, unsigned int type,
			unsigned int normalized, size_t size, const void* pointer) const = 0;

	protected:
		VertexBuffer(unsigned int drawMode)
			: m_rendererId(0), m_drawMode(drawMode) { }
		static VertexBuffer* Create(unsigned int drawMode);

	protected:
		friend Batch;

		unsigned int m_rendererId;
		unsigned int m_drawMode;
	};
}
