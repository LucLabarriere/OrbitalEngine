#include "OrbitalEngine/Components.h"
#include "OrbitalEngine/Logic.h"

namespace Orbital
{
	Entity::Entity(const LayerID& layerId, const entt::entity& handle)
		: mLayerId(layerId), mHandle(handle)
	{

	}

	Entity::Entity()
		: mLayerId(0), mHandle(entt::null)
	{

	}

	Entity::Entity(const Entity& e)
		: mLayerId(e.mLayerId), mHandle(e.mHandle)
	{

	}

	void Entity::ChangeLayer(LayerID layerId)
	{
		OE_NOT_IMPLEMENTED();
	}

	void Entity::Destroy()
	{
		auto& hierarchy = GetComponent<Hierarchy>();
		auto& children = hierarchy.getChildren();

		for (int i = children.size() - 1; i >= 0; i--)
		{
			children[i].Destroy();
		}

		hierarchy.getParent().GetComponent<Hierarchy>().removeChild(*this);

		auto mr = TryGetComponent<MeshRenderer>();
		if (mr) mr->destroy();

		(*sActiveScene)->DeleteEntity(mHandle, mLayerId);
	}

	bool Entity::IsValid() const
	{
		return mHandle != entt::null && (*sActiveScene)->IsValid(mHandle, mLayerId);
	}
}