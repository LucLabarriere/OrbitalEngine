#pragma once

namespace OrbitalEngine
{
	class FrameBuffer
	{
	public:
		virtual ~FrameBuffer() {};

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

	protected:
		FrameBuffer()
			: m_rendererId(0) { }
		static FrameBuffer* Create();

	protected:
		unsigned int m_rendererId;
	};
}