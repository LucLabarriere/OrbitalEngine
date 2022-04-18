#pragma once

#include "OrbitalEngine/Graphics/DynamicBatch.h"

namespace Orbital
{
	class DynamicBatchManager
	{
	public:
		DynamicBatchManager();

		void registerMesh(Components::MeshRenderer& mr, Components::Transform& t);
		void deleteMesh(Components::MeshRenderer& mr);
		void renderBatches();

	private:
		std::map<std::string, Ref<DynamicBatch>> m_batches;
	};
}
