#pragma once

#include "OrbitalEngine/Graphics/DynamicBatch.h"

namespace Orbital
{
	/* TODO
	class BatcheContainer
	public:
		const std::vector<Ref<DynamicBatch>>& getBatches() const { return m_batches; }

		std::vector<Ref<DynamicBatch>>::iterator begin() { return m_batches.begin(); }
		std::vector<Ref<DynamicBatch>>::iterator end() { return m_batches.end(); }
	
	private:
		std::vector<Ref<DynamicBatch>> m_batches
	* 
	* 
	* class DynamicBatchManager
	*	private: std::map<std::string, BatchContainer> m_bachContainers
	*/
	class DynamicBatchManager
	{
	public:
		DynamicBatchManager();

		void registerMesh(Components::MeshRenderer& mr, Components::Transform& t);
		void deleteMesh(Components::MeshRenderer& mr);
		void renderBatches();
		const std::map<std::string, Ref<DynamicBatch>>& getBatches() const { return m_batches; }

		std::map<std::string, Ref<DynamicBatch>>::iterator begin() { return m_batches.begin(); }
		std::map<std::string, Ref<DynamicBatch>>::iterator end() { return m_batches.end(); }

	private:
		std::map<std::string, Ref<DynamicBatch>> m_batches;
	};
}
