#pragma once

namespace Orbital
{
	class FrameBuffer
	{
	public:
		static FrameBuffer* Create();
		virtual ~FrameBuffer() {};

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void renderFrame() = 0;
		unsigned int getTextureId() const { return m_textureId; }


	protected:
		FrameBuffer() { }

	protected:
		unsigned int m_rendererId = 0;
		unsigned int m_textureId = 0;
	};
}