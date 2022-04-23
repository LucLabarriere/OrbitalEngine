#pragma once

#include "OrbitalEngine/Utils.h"
#include "OrbitalEngine/Graphics/RenderCommands.h"
#include "OrbitalEngine/Graphics/FrameBuffer.h"
#include "OrbitalEngine/Graphics/BatchManager.h"

namespace Orbital
{
	namespace Components
	{
		struct MeshRenderer;
		class Transform;
	}

	class Batch;

	class Renderer
	{
	public:
		static void inline Initialize()
		{
			if (s_instance == nullptr)
				s_instance = new Renderer();
			else
				OE_RAISE_SIGSEGV("Renderer: You're trying to initialize the Renderer again");
		}
		static void inline Terminate() { delete s_instance; RenderCommands::Terminate(); }
		static Renderer* Get() { return s_instance; }
		static WeakRef<BatchManager> GetBatchManager() { return s_instance->m_BatchManager; }

		static void RegisterMesh(Components::MeshRenderer& mr, Components::Transform& t) { s_instance->registerMesh(mr, t); }
		static void DeleteMesh(Components::MeshRenderer& mr) { s_instance->deleteMesh(mr); }
		static void RenderBatches() { s_instance->renderBatches(); }

		static void OnWindowResized();
		static unsigned int GetFrame() { return s_instance->getFrame(); }

		void newFrame();
		void displayFrame();

	private:
		Renderer();

		void onWindowResized();
		unsigned int getFrame() const { return m_frameBuffer->getTextureId(); }
		void registerMesh(Components::MeshRenderer& mr, Components::Transform& t);
		void deleteMesh(Components::MeshRenderer& mr);
		void renderBatches();

	private:
		static inline Renderer* s_instance = nullptr;
		Scope<FrameBuffer> m_frameBuffer;
		Ref<BatchManager> m_BatchManager;
	};
}