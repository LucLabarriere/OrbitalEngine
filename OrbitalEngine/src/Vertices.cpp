#include "OrbitalEngine/Graphics/Vertices.h"
#include "VertexBuffer.h"

namespace Orbital
{
	template<class ...Vertices>
	void VertexContainer<Vertices...>::allocateMemory(const VertexBuffer& buffer) const
	{
		buffer.allocateMemory(getData(), getSize());
	}

	template<class ...Vertices>
	void VertexContainer<Vertices...>::submitData(const VertexBuffer& buffer) const
	{
		buffer.submitData(getData(), getSize());
	}

	template<class ...Vertices>
	void VertexContainer<Vertices...>::setLayout(const VertexBuffer& buffer) const
	{
		std::vector<size_t> counts = { Vertices::GetCount() ... };
		std::vector<size_t> sizes = { Vertices::GetSize() ... };
		std::vector<unsigned int> types = { Vertices::GetType() ... };
		std::vector<unsigned int> norms = { Vertices::GetNormalized() ... };

		size_t offset = 0;
		size_t size = Vertex<Vertices...>::GetSize();

		for (size_t i = 0; i < counts.size(); i++)
		{
			buffer.setAttribute(i, counts[i], types[i], norms[i], size, (const void*)offset);
			offset += sizes[i];
		}
	}
}