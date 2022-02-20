#include "OrbitalEngine/Logic/LayerStack.h"

namespace OrbitalEngine
{
	LayerStack::LayerStack()
	{

	}

	LayerStack::~LayerStack()
	{

	}

	void LayerStack::push(Ref<Layer> layer)
	{
		m_layers.push_back(layer);
	}

	void LayerStack::pop(int layerId)
	{
		OE_RAISE_SIGSEGV("LayerStack: pop not implemented");
	}



	
}