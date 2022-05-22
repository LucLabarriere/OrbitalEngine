#pragma once

namespace Orbital
{
	class MultisampledFrameBuffer
	{
	public:
		static MultisampledFrameBuffer* Create();
		virtual ~MultisampledFrameBuffer() {};

		virtual void bind() const = 0;
		virtual void bindRead() const = 0;
		virtual void unbind() const = 0;

		virtual void renderFrame() = 0;
		unsigned int getTextureId() const { return m_textureId; }


	protected:
		MultisampledFrameBuffer() { }

	protected:
		unsigned int m_rendererId = 0;
		unsigned int m_textureId = 0;
	};
}