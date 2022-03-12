#include "OrbitalEngine/Graphics/RenderCommands.h"

namespace OrbitalEngine
{
	void RenderCommands::Initialize()
	{
		glad_glEnable(GL_DEPTH_TEST);
		glad_glDepthFunc(GL_LESS);
	}

	void RenderCommands::Terminate()
	{
		glfwTerminate();
	}

	void RenderCommands::NewFrame()
	{
		glad_glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		glad_glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glad_glEnable(GL_DEPTH_TEST);
	}

	void RenderCommands::DrawIndexed(unsigned int drawType, size_t indexCount)
	{
		glad_glDrawElements(drawType, indexCount, GL_UNSIGNED_INT, nullptr);
	}
}