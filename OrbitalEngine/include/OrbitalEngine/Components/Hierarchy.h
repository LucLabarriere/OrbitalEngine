#pragma once

#include "OrbitalEngine/Components/Component.h"
#include "OrbitalEngine/Utils/Misc.h"
#include "OrbitalEngine/Logic/Scene.h"

namespace Orbital
{
	class Scene;
	class Entity;

	class Hierarchy : public Component
	{
	public:
		Hierarchy(const Entity& entity, const Entity& parent);
		~Hierarchy();

		void SetParent(const Entity& parent);
		void RemoveChild(const Entity& entity);

		Entity& GetParent();
		std::vector<Entity>& GetChildren();

		std::vector<Entity>::iterator begin();
		std::vector<Entity>::iterator end();

	private:
		void AddChild(const Entity& child);

		Entity mParent;
		Entity mEntity;
		std::vector<Entity> mChildren;
	};
}