#pragma once

#include "OrbitalEngine/Logic/Layer.h"
#include "OrbitalEngine/Utils.h"

namespace OrbitalEngine
{
	class LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void push(Ref<Layer> layer);
		void pop(int layerId);

		Ref<Layer>& get(int layerId) { return m_layers[layerId]; }

		std::vector<Ref<Layer>>::reverse_iterator begin() { return m_layers.rbegin(); }
		std::vector<Ref<Layer>>::reverse_iterator end() { return m_layers.rend(); }

	private:
		std::vector<Ref<Layer>> m_layers;
	};
}
