#pragma once

namespace OrbitalEngine
{
	class RenderCommands
	{
	public:
		static void Initialize();
		static void Terminate();
		static void NewFrame();
		static void DrawIndexed(unsigned int drawType, size_t indexCount);
	};
}