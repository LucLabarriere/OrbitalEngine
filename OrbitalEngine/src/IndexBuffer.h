#pragma once

namespace Orbital
{
	class IndexBuffer
	{
	public:
		static IndexBuffer* Create(unsigned int drawMode);
		virtual ~IndexBuffer() { };
		
		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void allocateMemory(const void* data, size_t size) const = 0;
		virtual void submitData(const void* data, size_t size) const = 0;
		virtual void submitSubData(const void* data, size_t offset, size_t size) const = 0;
		
	protected:
		IndexBuffer(unsigned int drawMode)
			: m_rendererId(0), m_drawMode(drawMode) { }

	protected:
		unsigned int m_rendererId;
		unsigned int m_drawMode;
	};
}