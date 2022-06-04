#pragma once

namespace Orbital
{
	class IndexBuffer
	{
	public:
		static IndexBuffer* Create(unsigned int drawMode);
		virtual ~IndexBuffer() { };
		
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AllocateMemory(const void* data, size_t size) const = 0;
		virtual void SubmitData(const void* data, size_t size) const = 0;
		virtual void submitSubData(const void* data, size_t offset, size_t size) const = 0;
		
	protected:
		IndexBuffer(unsigned int drawMode)
			: mRendererId(0), mDrawMode(drawMode) { }

	protected:
		unsigned int mRendererId;
		unsigned int mDrawMode;
	};
}