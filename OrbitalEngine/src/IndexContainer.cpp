#include "OrbitalEngine/IndexContainer.h"
#include "IndexBuffer.h"

namespace OrbitalEngine
{
	void IndexContainer::allocateMemory(const IndexBuffer& buffer) const
	{
		buffer.allocateMemory(getData(), getSize());
	}

	void IndexContainer::submitData(const IndexBuffer& buffer) const
	{
		buffer.submitData(getData(), getSize());
	}
}