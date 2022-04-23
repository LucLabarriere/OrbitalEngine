#include "OrbitalEngine/Graphics.h"

namespace Orbital
{
	void Renderer::OnWindowResized()
	{
		s_instance->onWindowResized();
	}

	void Renderer::newFrame()
	{
		Metrics::ReinitializeBatchCount();
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
		, m_BatchManager(new BatchManager)
	{
		RenderCommands::Initialize();
	}

	void Renderer::onWindowResized()
	{
		m_frameBuffer.reset(FrameBuffer::Create());
	}

	void Renderer::registerMesh(Components::MeshRenderer& mr, Components::Transform& t)
	{
		m_BatchManager->registerMesh(mr, t);
	}

	void Renderer::deleteMesh(Components::MeshRenderer& mr)
	{
		m_BatchManager->deleteMesh(mr);
	}

	void Renderer::renderBatches()
	{
		m_BatchManager->renderBatches();
	}
}