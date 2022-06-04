#include "OpenGLFrameBuffer.h"
#include "OrbitalEngine/Utils.h"
#include "OrbitalEngine/Graphics.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace Orbital
{
	FrameBuffer* FrameBuffer::Create()
	{
		return new OpenGLFrameBuffer();
	}

	OpenGLFrameBuffer::~OpenGLFrameBuffer()
	{
		glad_glDeleteFramebuffers(1, &mRendererId);
		glad_glDeleteTextures(1, &mTextureId);
		glad_glDeleteRenderbuffers(1, &m_renderBufferId);
	}

	void OpenGLFrameBuffer::Bind() const
	{
		glad_glBindFramebuffer(GL_FRAMEBUFFER, mRendererId);
	}

	void OpenGLFrameBuffer::BindDraw() const
	{
		glad_glBindFramebuffer(GL_DRAW_FRAMEBUFFER, mRendererId);
	}

	void OpenGLFrameBuffer::Unbind() const
	{
		glad_glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFrameBuffer::RenderFrame()
	{
		auto shader = ShaderManager::Get("PostProcess").lock();
		shader->Bind();
		glad_glDisable(GL_DEPTH_TEST);
		glad_glActiveTexture(GL_TEXTURE0);
		glad_glBindTexture(GL_TEXTURE_2D, mTextureId);
		shader->SetUniform1i("u_ScreenTexture", 0);

		mVao->Bind();
		mIbo->Bind();

		RenderCommands::DrawIndexed(OE_TRIANGLES, 6);
	}

	OpenGLFrameBuffer::OpenGLFrameBuffer()
	{
		unsigned int width = Settings::Get(Settings::UIntSetting::RenderingAreaWidth);
		unsigned int height = Settings::Get(Settings::UIntSetting::RenderingAreaHeight);

		glad_glGenFramebuffers(1, &mRendererId);
		glBindFramebuffer(GL_FRAMEBUFFER, mRendererId);
		glad_glActiveTexture(GL_TEXTURE0);
		glad_glGenTextures(1, &mTextureId);
		glad_glBindTexture(GL_TEXTURE_2D, mTextureId);

		glad_glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

		glad_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glad_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glad_glBindTexture(GL_TEXTURE_2D, 0);
		glad_glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mTextureId, 0);

		glad_glGenRenderbuffers(1, &m_renderBufferId);
		glad_glBindRenderbuffer(GL_RENDERBUFFER, m_renderBufferId);

		glad_glRenderbufferStorage(
			GL_RENDERBUFFER, GL_DEPTH24_STENCIL8,
			width, height
		);

		glad_glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_renderBufferId);
		glad_glBindRenderbuffer(GL_RENDERBUFFER, 0);

		OE_ASSERT(
			glad_glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE,
			"OpenGLFrameBuffer: An error occured with a framebuffer"
		);

		glad_glBindFramebuffer(GL_FRAMEBUFFER, 0);

		const auto& screenMesh = MeshManager::Get("Quad");
		const auto& vertices = screenMesh.lock()->GetVertices();
		const auto& indices = screenMesh.lock()->getIndices();

		mVao = Scope<VertexArray>(VertexArray::Create());
		mVbo = Scope<VertexBuffer>(VertexBuffer::Create(OE_STATIC_DRAW));
		mVao->Bind();
		mVbo->Bind();
		mVbo->AllocateMemory(vertices.GetData(), vertices.GetSize());

		mIbo = Scope<IndexBuffer>(IndexBuffer::Create(OE_STATIC_DRAW));
		mIbo->AllocateMemory(indices.GetData(), indices.GetSize());

		vertices.SetLayout(*mVbo);

		glad_glViewport(0, 0, width, height);
	}
}