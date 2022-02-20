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

		friend FrameBuffer;
	};
}