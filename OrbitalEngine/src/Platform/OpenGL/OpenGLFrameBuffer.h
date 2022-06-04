#pragma once
#include "OrbitalEngine/Graphics/FrameBuffer.h"
#include "OrbitalEngine/Components/Transform.h"
#include "OrbitalEngine/Components/MeshRenderer.h"

namespace Orbital
{
	class VertexArray;
	class VertexBuffer;
	class IndexBuffer;

	class OpenGLFrameBuffer: public FrameBuffer
	{
	public:
		virtual ~OpenGLFrameBuffer() override;

		virtual void bind() const override;
		virtual void bindDraw() const override;
		virtual void unbind() const override;

		virtual void renderFrame() override;

	private:
		OpenGLFrameBuffer();

	private:
		friend FrameBuffer;

		unsigned int m_renderBufferId;
		Scope<VertexArray> m_vao;
		Scope<VertexBuffer> m_vbo;
		Scope<IndexBuffer> m_ibo;
		const Transform m_screenTransform = {
			{ 0.0f, 0.0f, 0.0f },
			{ 0.0f, 0.0f, 0.0f },
			{ 2.0f, 2.0f, 0.0f }
		};
	};
}