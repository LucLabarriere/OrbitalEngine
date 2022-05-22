#include "OrbitalEngine/Graphics.h"
#include "OrbitalEngine/Components/MeshRenderer.h"
#include "OrbitalEngine/Components/Transform.h"

namespace Orbital
{
	void Renderer::InitializeFramebuffer()
	{
		s_instance->m_frameBuffer = Scope<FrameBuffer>(FrameBuffer::Create());
	}
	void Renderer::InitializeBatchManager()
	{
		s_instance->m_batchManager = CreateRef<BatchManager>();
	}

	void Renderer::PushBufferUnit(WeakRef<Mesh> mesh)
	{
		s_instance->m_unitManager->push(mesh);
	}

	void Renderer::PushBufferUnit(WeakRef<Material> material, bool fill)
	{
		s_instance->m_unitManager->push(material, fill);
	}

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
		: m_frameBuffer(nullptr)
		, m_batchManager(nullptr)
		, m_unitManager(new BufferUnitManager)
	{
		RenderCommands::Initialize();
	}

	void Renderer::onWindowResized()
	{
		m_frameBuffer.reset(FrameBuffer::Create());
	}

	void Renderer::registerMesh(Components::MeshRenderer& mr, Components::Transform& t)
	{
		auto drawData = mr.getDrawData();

		if (drawData.batchDraw)
		{
			m_batchManager->registerMesh(mr, t);
		}
		else
		{
			m_unitManager->registerMesh(mr, t);
		}
	}

	void Renderer::deleteMesh(Components::MeshRenderer& mr)
	{
		auto drawData = mr.getDrawData();

		if (drawData.batchDraw)
		{
			m_batchManager->deleteMesh(mr);
		}
	}

	void Renderer::renderBatches()
	{
		m_batchManager->renderBatches();
	}

	void Renderer::renderUnits()
	{
		m_unitManager->renderUnits();
	}
}