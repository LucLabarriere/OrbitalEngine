#pragma once

#include "OrbitalEngine/Graphics/Vertices.h"

namespace Orbital
{
	class VertexBuffer
	{
	public:
		static VertexBuffer* Create(unsigned int drawMode);
		virtual ~VertexBuffer() {};

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void allocateMemory(const void* data, size_t size) const = 0;
		virtual void submitData(const void* data, size_t size) const = 0;
		virtual void submitSubData(const void* data, size_t offset, size_t size) const = 0;
		virtual void setAttribute(size_t index, size_t count, unsigned int type,
			unsigned int normalized, size_t size, const void* pointer) const = 0;

	protected:
		VertexBuffer(unsigned int drawMode)
			: m_rendererId(0), m_drawMode(drawMode) { }

	protected:
		unsigned int m_rendererId;
		unsigned int m_drawMode;
	};
}
