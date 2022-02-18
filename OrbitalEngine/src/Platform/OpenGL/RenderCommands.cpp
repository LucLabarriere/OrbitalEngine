#include "OrbitalEngine/RenderCommands.h"

namespace OrbitalEngine
{
	void RenderCommands::Initialize()
	{

	}

	void RenderCommands::Terminate()
	{
		glfwTerminate();
	}

	void RenderCommands::NewFrame()
	{
		glad_glClearColor(0.1f, 0.0f, 0.0f, 1.0f);
		glad_glClear(GL_COLOR_BUFFER_BIT);
	}

	void RenderCommands::DrawIndexed(unsigned int drawType, size_t indexCount)
	{
		glad_glDrawElements(drawType, indexCount, GL_UNSIGNED_INT, nullptr);
	}
}