#include "OrbitalEngine/Graphics/RenderCommands.h"

namespace Orbital
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
		glad_glClearColor(0.3f, 0.5f, 1.0f, 1.0f);
		glad_glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glad_glEnable(GL_DEPTH_TEST);
	}

	void RenderCommands::ReadyFrame()
	{
		glad_glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glad_glClear(GL_COLOR_BUFFER_BIT);
	}

	void RenderCommands::DisableDepthTest()
	{
		glad_glDisable(GL_DEPTH_TEST);
	}

	void RenderCommands::DrawIndexed(unsigned int drawType, size_t size)
	{
		glad_glDrawElements(drawType, size, GL_UNSIGNED_INT, nullptr);
	}
}