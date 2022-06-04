#pragma once

#include "OrbitalEngine/Utils.h"
#include "OrbitalEngine/Graphics/RenderCommands.h"
#include "OrbitalEngine/Graphics/FrameBuffer.h"
#include "OrbitalEngine/Graphics/MultisampledFrameBuffer.h"
#include "OrbitalEngine/Graphics/BatchManager.h"
#include "OrbitalEngine/Graphics/BufferUnitManager.h"

namespace Orbital
{
	class MeshRenderer;
	class Transform;
	class Batch;

	class Renderer
	{
	public:
		static void inline Initialize()
		{
			if (sInstance == nullptr)
				sInstance = new Renderer();
			else
				OE_RAISE_SIGSEGV("Renderer: You're trying to initialize the Renderer again");
		}
		static void InitializeFramebuffers();
		static void InitializeBatchManager();

		static void inline Terminate() { delete sInstance; RenderCommands::Terminate(); }
		static Renderer* Get() { return sInstance; }
		static WeakRef<BatchManager> GetBatchManager() { return sInstance->mBatchManager; }

		static void RegisterMesh(MeshRenderer& mr, Transform& t) { sInstance->RegisterMeshImpl(mr, t); }
		static void DeleteMesh(MeshRenderer& mr) { sInstance->DeleteMeshImpl(mr); }
		static void PushBufferUnit(WeakRef<Mesh> mesh);
		static void PushBufferUnit(WeakRef<Material> material, bool fill = true);

		static void RenderBatches() { sInstance->RenderBatchesImpl(); }
		static void RenderUnits() { sInstance->RenderUnitsImpl(); }

		static void OnWindowResized();
		static unsigned int GetFrame() { return sInstance->GetFrameImpl(); }

		void NewFrame();
		void DisplayFrame();

	private:
		Renderer();

		void OnWindowResizedImpl();
		unsigned int GetFrameImpl() const { return mFrameBuffer->GetTextureId(); }
		void RegisterMeshImpl(MeshRenderer& mr, Transform& t);
		void DeleteMeshImpl(MeshRenderer& mr);
		void RenderBatchesImpl();
		void RenderUnitsImpl();

	private:
		static inline Renderer* sInstance = nullptr;
		Scope<FrameBuffer> mFrameBuffer;
		Scope<MultisampledFrameBuffer> mMSFrameBuffer;
		Ref<BatchManager> mBatchManager;
		Ref<BufferUnitManager> mUnitManager;
	};
}