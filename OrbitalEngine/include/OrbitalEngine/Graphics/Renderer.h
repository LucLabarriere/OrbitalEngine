#pragma once

#include "OrbitalEngine/Utils.h"
#include "OrbitalEngine/Graphics/RenderCommands.h"
#include "OrbitalEngine/Graphics/FrameBuffer.h"

namespace Orbital
{
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

		static void Submit(Ref<Batch>& batch);
		static void OnWindowResized();
		static unsigned int GetFrame() { return s_instance->getFrame(); }

		void newFrame();
		void displayFrame();

	private:
		Renderer();

		void onWindowResized();
		unsigned int getFrame() const { return m_frameBuffer->getTextureId(); }

	private:
		static inline Renderer* s_instance = nullptr;
		Scope<FrameBuffer> m_frameBuffer;
	};
}