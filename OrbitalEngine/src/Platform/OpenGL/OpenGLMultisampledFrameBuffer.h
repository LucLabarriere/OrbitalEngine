#pragma once
#include "OrbitalEngine/Graphics/MultisampledFrameBuffer.h"
#include "OrbitalEngine/Components/Transform.h"
#include "OrbitalEngine/Components/MeshRenderer.h"

namespace Orbital
{
	class VertexArray;
	class VertexBuffer;
	class IndexBuffer;

	class OpenGLMultisampledFrameBuffer: public MultisampledFrameBuffer
	{
	public:
		virtual ~OpenGLMultisampledFrameBuffer() override;

		virtual void bind() const override;
		virtual void bindRead() const override;
		virtual void unbind() const override;

		virtual void renderFrame() override;

	private:
		OpenGLMultisampledFrameBuffer();

	private:
		friend MultisampledFrameBuffer;

		unsigned int m_renderBufferId;
		Scope<VertexArray> m_vao;
		Scope<VertexBuffer> m_vbo;
		Scope<IndexBuffer> m_ibo;
		const Components::Transform m_screenTransform = {
			{ 0.0f, 0.0f, 0.0f },
			{ 0.0f, 0.0f, 0.0f },
			{ 2.0f, 2.0f, 0.0f }
		};
	};
}