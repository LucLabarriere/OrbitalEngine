#pragma once

namespace Orbital
{
	class FrameBuffer
	{
	public:
		static FrameBuffer* Create();
		virtual ~FrameBuffer() {};

		virtual void Bind() const = 0;
		virtual void BindDraw() const = 0;
		virtual void Unbind() const = 0;

		virtual void RenderFrame() = 0;
		unsigned int GetTextureId() const { return mTextureId; }


	protected:
		FrameBuffer() { }

	protected:
		unsigned int mRendererId = 0;
		unsigned int mTextureId = 0;
	};
}