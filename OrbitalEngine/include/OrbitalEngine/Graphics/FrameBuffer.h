#pragma once

namespace OrbitalEngine
{
	class Renderer;

	class FrameBuffer
	{
	public:
			virtual ~FrameBuffer() {};

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void renderFrame() = 0;
		unsigned int getTextureId() const { return m_textureId; }

	protected:
		FrameBuffer() : m_rendererId(0) { }
		static FrameBuffer* Create();

	protected:
		friend Renderer;
		unsigned int m_rendererId;
		unsigned int m_textureId;
	};
}