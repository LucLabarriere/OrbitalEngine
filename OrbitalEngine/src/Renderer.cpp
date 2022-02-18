#pragma once
#include "OrbitalEngine/Renderer.h"
#include "OrbitalEngine/Batch.h"

namespace OrbitalEngine
{
	void Renderer::Submit(Ref<Batch>& batch)
	{
		batch->bind();
		RenderCommands::DrawIndexed(batch->getDrawType(), batch->getIndexContainerCount());
		batch->requestDraw(false);
	}
}