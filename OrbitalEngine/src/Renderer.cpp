#include "OrbitalEngine/Graphics/Renderer.h"
#include "OrbitalEngine/Graphics/Batch.h"

namespace OrbitalEngine
{
	void Renderer::Submit(Ref<Batch>& batch)
	{
		batch->bind();
		RenderCommands::DrawIndexed(batch->getDrawType(), batch->getIndexContainerCount());
		batch->requestDraw(false);
	}
}