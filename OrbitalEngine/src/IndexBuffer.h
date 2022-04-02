#pragma once

namespace Orbital
{
	class Batch;

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() { };
		
		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void allocateMemory(const void* data, size_t size) const = 0;
		virtual void submitData(const void* data, size_t size) const = 0;
		
	protected:
		IndexBuffer(unsigned int drawMode)
			: m_rendererId(0), m_drawMode(drawMode) { }
		static IndexBuffer* Create(unsigned int drawMode);

	protected:
		friend Batch;
		
		unsigned int m_rendererId;
		unsigned int m_drawMode;
	};
}