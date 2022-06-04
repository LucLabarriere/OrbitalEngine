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

		virtual void Bind() const override;
		virtual void bindRead() const override;
		virtual void Unbind() const override;

		virtual void RenderFrame() override;

	private:
		OpenGLMultisampledFrameBuffer();

	private:
		friend MultisampledFrameBuffer;

		unsigned int m_renderBufferId;
		Scope<VertexArray> mVao;
		Scope<VertexBuffer> mVbo;
		Scope<IndexBuffer> mIbo;
		const Transform m_screenTransform = {
			{ 0.0f, 0.0f, 0.0f },
			{ 0.0f, 0.0f, 0.0f },
			{ 2.0f, 2.0f, 0.0f }
		};
	};
}