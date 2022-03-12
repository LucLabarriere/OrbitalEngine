#pragma once
#include "FrameBuffer.h"

namespace OrbitalEngine
{
	class OpenGLFrameBuffer: public FrameBuffer
	{
	public:
		virtual ~OpenGLFrameBuffer() override;

		virtual void bind() const override;
		virtual void unbind() const override;

	private:
		OpenGLFrameBuffer();

		unsigned int m_renderBufferId;
		unsigned int m_textureId;

		friend FrameBuffer;
	};
}