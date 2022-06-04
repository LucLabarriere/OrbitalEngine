#include "OrbitalEngine/Graphics/IndexContainer.h"
#include "IndexBuffer.h"

namespace Orbital
{
	void IndexContainer::AllocateMemory(const IndexBuffer& buffer) const
	{
		buffer.AllocateMemory(GetData(), GetSize());
	}

	void IndexContainer::SubmitData(const IndexBuffer& buffer) const
	{
		buffer.SubmitData(GetData(), GetSize());
	}
}