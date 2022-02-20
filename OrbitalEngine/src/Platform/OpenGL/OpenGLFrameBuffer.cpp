#include "OpenGLFrameBuffer.h"

namespace OrbitalEngine
{
	FrameBuffer* FrameBuffer::Create()
	{
		return new OpenGLFrameBuffer();
	}

	OpenGLFrameBuffer::~OpenGLFrameBuffer()
	{
		glad_glDeleteFramebuffers(1, &m_rendererId);
	}

	void OpenGLFrameBuffer::bind() const
	{
		glad_glBindFramebuffer(GL_FRAMEBUFFER, m_rendererId);
	}

	void OpenGLFrameBuffer::unbind() const
	{
		glad_glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}