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
		Metrics::Get<unsigned int>(Metric::BatchCount) += 1;

		batch->requestDraw(false);
	}

	void Renderer::OnWindowResized()
	{
		s_instance->onWindowResized();
	}

	void Renderer::newFrame()
	{
		Metrics::Get<unsigned int>(Metric::BatchCount) = -1;
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

	void Renderer::onWindowResized()
	{
		m_frameBuffer.reset(FrameBuffer::Create());
	}
}