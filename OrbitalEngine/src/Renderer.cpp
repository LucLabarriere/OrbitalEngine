#include "OrbitalEngine/Graphics.h"

namespace OrbitalEngine
{
	void Renderer::Submit(Ref<Batch>& batch)
	{
		batch->bind();

		RenderCommands::DrawIndexed(
			batch->getDrawType(),
			batch->getIndexContainerCount()
		);

		batch->requestDraw(false);
	}

	void Renderer::newFrame()
	{
		m_frameBuffer->bind();
		RenderCommands::NewFrame();
	}

	void Renderer::displayFrame()
	{
		m_frameBuffer->unbind();
		RenderCommands::ReadyFrame();
		m_frameBuffer->renderFrame();
	}

	Renderer::Renderer()
		: m_frameBuffer(FrameBuffer::Create())
	{
		RenderCommands::Initialize();
	}
}