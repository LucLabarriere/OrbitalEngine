#pragma once
#include "OrbitalEngine/Graphics/FrameBuffer.h"
#include "OrbitalEngine/Components.h"

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
		Ref<Mesh> m_screenMesh;
		Ref<Batch> m_batch;
		Components::Transform m_screenTransform;
	};
}