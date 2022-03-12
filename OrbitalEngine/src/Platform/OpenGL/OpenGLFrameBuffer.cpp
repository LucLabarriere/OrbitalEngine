#include "OpenGLFrameBuffer.h"
#include "OrbitalEngine/Utils.h"

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

	OpenGLFrameBuffer::OpenGLFrameBuffer()
	{
		glad_glGenFramebuffers(1, &m_rendererId);
		glBindFramebuffer(GL_FRAMEBUFFER, m_rendererId);
		glad_glActiveTexture(GL_TEXTURE0);
		glad_glGenTextures(1, &m_textureId);
		glad_glBindTexture(GL_TEXTURE_2D, m_textureId);

		glad_glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glad_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glad_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glad_glBindTexture(GL_TEXTURE_2D, 0);
		glad_glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_textureId, 0);

		glad_glGenRenderbuffers(1, &m_renderBufferId);
		glad_glBindRenderbuffer(GL_RENDERBUFFER, m_renderBufferId);
		glad_glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 600);
		glad_glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_renderBufferId);
		glad_glBindRenderbuffer(GL_RENDERBUFFER, 0);

		OE_ASSERT(
			glad_glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE,
			"OpenGLFrameBuffer: An error occured with a framebuffer"
		);

		glad_glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}