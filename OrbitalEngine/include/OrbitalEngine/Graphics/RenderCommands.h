#pragma once

namespace OrbitalEngine
{
	class RenderCommands
	{
	public:
		static void Initialize();
		static void Terminate();
		static void NewFrame();
		static void ReadyFrame();
		static void DisableDepthTest();
		static void DrawIndexed(unsigned int drawType, size_t indexCount);
	};
}