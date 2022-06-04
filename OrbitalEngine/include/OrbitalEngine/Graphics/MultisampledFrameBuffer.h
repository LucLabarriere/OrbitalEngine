#pragma once

namespace Orbital
{
	class MultisampledFrameBuffer
	{
	public:
		static MultisampledFrameBuffer* Create();
		virtual ~MultisampledFrameBuffer() {};

		virtual void Bind() const = 0;
		virtual void bindRead() const = 0;
		virtual void Unbind() const = 0;

		virtual void RenderFrame() = 0;
		unsigned int GetTextureId() const { return mTextureId; }


	protected:
		MultisampledFrameBuffer() { }

	protected:
		unsigned int mRendererId = 0;
		unsigned int mTextureId = 0;
	};
}