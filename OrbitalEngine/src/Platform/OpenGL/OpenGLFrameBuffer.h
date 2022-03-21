#pragma once
#include "OrbitalEngine/Graphics/FrameBuffer.h"
#include "OrbitalEngine/Components/Transform.h"
#include "OrbitalEngine/Components/MeshRenderer.h"

namespace OrbitalEngine
{
	class Batch;

	class OpenGLFrameBuffer: public FrameBuffer
	{
	public:
		virtual ~OpenGLFrameBuffer() override;

		virtual void bind() const override;
		virtual void unbind() const override;

		virtual void renderFrame() override;

	private:
		OpenGLFrameBuffer();

	private:
		friend FrameBuffer;

		unsigned int m_renderBufferId;
		Ref<Batch> m_batch;
		const Components::Transform m_screenTransform = {
			{ 0.0f, 0.0f, 0.0f },
			{ 0.0f, 0.0f, 0.0f },
			{ 2.0f, 2.0f, 0.0f }
		};
	};
}