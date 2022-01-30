#pragma once
#include "OrbitalEngine/Vertices.h"
#include "VertexBuffer.h"

namespace OrbitalEngine
{
	template<class ...Vertices>
	void VertexContainer<Vertices...>::allocateMemory(const VertexBuffer& buffer) const
	{
		buffer.allocateMemory(getData(), getSize());
	}

	template<class ...Vertices>
	void VertexContainer<Vertices...>::setLayout(const VertexBuffer& buffer) const
	{
		std::vector<unsigned int> counts = { Vertices::GetCount() ... };
		std::vector<unsigned int> sizes = { Vertices::GetSize() ... };
		std::vector<unsigned int> types = { Vertices::GetType() ... };
		std::vector<unsigned int> norms = { Vertices::GetNormalized() ... };

		unsigned int offset = 0;
		unsigned int size = Vertex<Vertices...>::GetSize();

		for (unsigned int i = 0; i < counts.size(); i++)
		{
			buffer.setAttribute(i, counts[i], types[i], norms[i], size, (const void*)offset);
			offset += sizes[i];
		}
	}
}