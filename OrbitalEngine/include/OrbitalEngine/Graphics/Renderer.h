#pragma once

#include "OrbitalEngine/Utils.h"
#include "OrbitalEngine/Graphics/RenderCommands.h"

namespace OrbitalEngine
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

		void newFrame() { RenderCommands::NewFrame(); }



	private:
		Renderer() { RenderCommands::Initialize(); }

	private:
		static inline Renderer* s_instance = nullptr;
	};
}