#include "OpenGLMultisampledFrameBuffer.h"
#include "OrbitalEngine/Utils.h"
#include "OrbitalEngine/Graphics.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace Orbital
{
	MultisampledFrameBuffer* MultisampledFrameBuffer::Create()
	{
		return new OpenGLMultisampledFrameBuffer();
	}

	OpenGLMultisampledFrameBuffer::~OpenGLMultisampledFrameBuffer()
	{
		glad_glDeleteFramebuffers(1, &m_rendererId);
		glad_glDeleteTextures(1, &m_textureId);
		glad_glDeleteRenderbuffers(1, &m_renderBufferId);
	}

	void OpenGLMultisampledFrameBuffer::bind() const
	{
		glad_glBindFramebuffer(GL_FRAMEBUFFER, m_rendererId);
	}

	void OpenGLMultisampledFrameBuffer::bindRead() const
	{
		glad_glBindFramebuffer(GL_READ_FRAMEBUFFER, m_rendererId);
	}

	void OpenGLMultisampledFrameBuffer::unbind() const
	{
		glad_glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLMultisampledFrameBuffer::renderFrame()
	{
		auto shader = ShaderManager::Get("PostProcess").lock();
		shader->bind();
		glad_glDisable(GL_DEPTH_TEST);
		glad_glActiveTexture(GL_TEXTURE0);
		glad_glBindSampler(0, 0);
		glad_glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, m_textureId);
		shader->setUniform1i("u_ScreenTexture", 0);

		m_vao->bind();
		m_ibo->bind();

		RenderCommands::DrawIndexed(
			OE_TRIANGLES, 6
		);
	}

	OpenGLMultisampledFrameBuffer::OpenGLMultisampledFrameBuffer()
	{
		unsigned int width = Settings::Get(Settings::UIntSetting::RenderingAreaWidth);
		unsigned int height = Settings::Get(Settings::UIntSetting::RenderingAreaHeight);
		unsigned int samples = 8;

		glad_glGenFramebuffers(1, &m_rendererId);
		glBindFramebuffer(GL_FRAMEBUFFER, m_rendererId);
		glad_glActiveTexture(GL_TEXTURE0);
		glad_glGenTextures(1, &m_textureId);
		glad_glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, m_textureId);

		glad_glTexImage2DMultisample(
			GL_TEXTURE_2D_MULTISAMPLE, samples, GL_RGB,
			width, height, GL_TRUE
		);

		glad_glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glad_glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glad_glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
		glad_glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, m_textureId, 0);

		glad_glGenRenderbuffers(1, &m_renderBufferId);
		glad_glBindRenderbuffer(GL_RENDERBUFFER, m_renderBufferId);

		glad_glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, GL_DEPTH24_STENCIL8, width, height );

		glad_glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_renderBufferId);
		glad_glBindRenderbuffer(GL_RENDERBUFFER, 0);

		OE_ASSERT(
			glad_glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE,
			"OpenGLFrameBuffer: An error occured with a framebuffer"
		);

		glad_glBindFramebuffer(GL_FRAMEBUFFER, 0);

		const auto& screenMesh = MeshManager::Get("Quad");
		const auto& vertices = screenMesh.lock()->getVertices();
		const auto& indices = screenMesh.lock()->getIndices();

		m_vao = Scope<VertexArray>(VertexArray::Create());
		m_vbo = Scope<VertexBuffer>(VertexBuffer::Create(OE_STATIC_DRAW));
		m_vao->bind();
		m_vbo->bind();
		m_vbo->allocateMemory(vertices.getData(), vertices.getSize());

		m_ibo = Scope<IndexBuffer>(IndexBuffer::Create(OE_STATIC_DRAW));
		m_ibo->allocateMemory(indices.getData(), indices.getSize());

		vertices.setLayout(*m_vbo);

		glad_glViewport(0, 0, width, height);
	}
}