#include "OrbitalEngine/Graphics.h"
#include "OrbitalEngine/Components/MeshRenderer.h"
#include "OrbitalEngine/Components/Transform.h"

namespace Orbital
{
	void Renderer::InitializeFramebuffers()
	{
		sInstance->mFrameBuffer = Scope<FrameBuffer>(FrameBuffer::Create());
		sInstance->mMSFrameBuffer = Scope<MultisampledFrameBuffer>(MultisampledFrameBuffer::Create());
	}
	void Renderer::InitializeBatchManager()
	{
		sInstance->mBatchManager = CreateRef<BatchManager>();
	}

	void Renderer::PushBufferUnit(WeakRef<Mesh> mesh)
	{
		sInstance->mUnitManager->Push(mesh);
	}

	void Renderer::PushBufferUnit(WeakRef<Material> material, bool fill)
	{
		sInstance->mUnitManager->Push(material, fill);
	}

	void Renderer::OnWindowResized()
	{
		sInstance->OnWindowResizedImpl();
	}

	void Renderer::NewFrame()
	{
		Metrics::ReinitializeBatchCount();
		mMSFrameBuffer->Bind();
		RenderCommands::NewFrame();
	}

	void Renderer::DisplayFrame()
	{
		mFrameBuffer->Unbind();
		mMSFrameBuffer->bindRead();
		mFrameBuffer->BindDraw();
		RenderCommands::BlitFramebuffer();
		mFrameBuffer->Unbind();
		RenderCommands::ReadyFrame();
		mFrameBuffer->RenderFrame();
	}

	Renderer::Renderer()
		: mFrameBuffer(nullptr)
		, mBatchManager(nullptr)
		, mUnitManager(new BufferUnitManager)
	{
		RenderCommands::Initialize();
	}

	void Renderer::OnWindowResizedImpl()
	{
		mFrameBuffer.reset(FrameBuffer::Create());
	}

	void Renderer::RegisterMeshImpl(MeshRenderer& mr, Transform& t)
	{
		auto drawData = mr.GetDrawData();

		if (drawData.batchDraw)
		{
			mBatchManager->RegisterMesh(mr, t);
		}
		else
		{
			mUnitManager->RegisterMesh(mr, t);
		}
	}

	void Renderer::DeleteMeshImpl(MeshRenderer& mr)
	{
		auto drawData = mr.GetDrawData();

		if (drawData.batchDraw)
		{
			mBatchManager->DeleteMesh(mr);
		}
	}

	void Renderer::RenderBatchesImpl()
	{
		mBatchManager->RenderBatches();
	}

	void Renderer::RenderUnitsImpl()
	{
		mUnitManager->RenderUnits();
	}
}