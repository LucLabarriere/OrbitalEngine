#include "OrbitalEngine/Components/Hierarchy.h"
#include "OrbitalEngine/Logic/Scene.h"

namespace Orbital
{
	Hierarchy::Hierarchy(const Entity& entity, const Entity& parent)
		: mEntity(entity), mParent(parent)
	{
		if (mParent.IsValid())
			mParent.GetComponent<Hierarchy>().AddChild(mEntity);
	}

	Hierarchy::~Hierarchy()
	{

	}

	void Hierarchy::SetParent(const Entity& parent)
	{
		// Removing former parent
		auto& parentHierarchy = mParent.GetComponent<Hierarchy>();
		parentHierarchy.RemoveChild(mEntity);

		// Setting new parent
		mParent = Entity(parent);
		mParent.GetComponent<Hierarchy>().AddChild(mEntity);
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

	std::vector<Entity>& Hierarchy::GetChildren()
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