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
		auto& children = hierarchy.GetChildren();

		for (int i = children.size() - 1; i >= 0; i--)
		{
			children[i].Destroy();
		}

		hierarchy.GetParent().GetComponent<Hierarchy>().RemoveChild(*this);

		auto mr = TryGetComponent<MeshRenderer>();
		if (mr) mr->Destroy();

		OE::ActiveScene->DeleteEntity(mHandle, mLayerId);
	}

	bool Entity::IsValid() const
	{
		return mHandle != entt::null && OE::ActiveScene->IsValid(mHandle, mLayerId);
	}

	Entity Entity::FromUUID(const UUID& uuid)
	{
		return OE::ActiveScene->GetEntity(uuid);
	}
}