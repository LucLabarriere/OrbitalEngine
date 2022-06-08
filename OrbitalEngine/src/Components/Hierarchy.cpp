#include "OrbitalEngine/Components/Hierarchy.h"
#include "OrbitalEngine/Logic/Scene.h"

namespace Orbital
{
	Hierarchy::Hierarchy()
		: mEntity(Entity()), mParent(Entity())
	{

	}

	Hierarchy::Hierarchy(const Entity& entity, const Entity& parent)
		: mEntity(entity), mParent(parent)
	{
		if (mParent.IsValid())
			mParent.GetComponent<Hierarchy>().AddChild(mEntity);
	}

	Hierarchy::~Hierarchy()
	{

	}

	void Hierarchy::SetEntity(const Entity& entity)
	{
		mEntity = entity;
	}

	void Hierarchy::SetParent(const Entity& parent)
	{
		// Removing former parent
		if (mParent.IsValid())
		{
			auto& parentHierarchy = mParent.GetComponent<Hierarchy>();
			parentHierarchy.RemoveChild(mEntity);
		}

		// Setting new parent
		mParent = parent;

		if (mParent.IsValid())
			mParent.GetComponent<Hierarchy>().AddChild(mEntity);
	}

	void Hierarchy::SetParent(const UUID& uuid)
	{
		if (OE::ActiveScene->IsValid(uuid))
			SetParent(Entity::FromUUID(uuid));
		else
			SetParent(Entity());
	}

	void Hierarchy::RemoveChild(const Entity& entity)
	{
		for (size_t i = 0; i < mChildren.size(); i++)
			if (mChildren[i].GetComponent<UUID>() == entity.GetComponent<UUID>())
				mChildren.erase(mChildren.begin() + i);
	}

	Entity& Hierarchy::GetParent()
	{
		return mParent;
	}

	const Entity& Hierarchy::GetParent() const
	{
		return mParent;
	}

	std::vector<Entity>& Hierarchy::GetChildren()
	{
		return mChildren;
	}

	const std::vector<Entity>& Hierarchy::GetChildren() const
	{
		return mChildren;
	}

	std::vector<Entity>::iterator Hierarchy::begin()
	{
		return mChildren.begin();
	}

	std::vector<Entity>::iterator Hierarchy::end()
	{
		return mChildren.end();
	}

	void Hierarchy::AddChild(const Entity& child)
	{
		mChildren.push_back(child);
	}
}