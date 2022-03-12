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
		RenderCommands::NewFrame();
	}

	void Renderer::displayFrame()
	{

	}

	Renderer::Renderer()
	{
		RenderCommands::Initialize();
		m_frameBuffer = CreateScope<FrameBuffer>();
	}
}