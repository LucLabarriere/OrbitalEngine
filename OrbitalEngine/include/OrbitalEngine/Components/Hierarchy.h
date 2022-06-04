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

		void setParent(const Entity& parent);
		void removeChild(const Entity& entity);

		Entity& getParent();
		std::vector<Entity>& getChildren();

		std::vector<Entity>::iterator begin();
		std::vector<Entity>::iterator end();

	private:
		void addChild(const Entity& child);

		Entity m_parent;
		Entity m_entity;
		std::vector<Entity> m_children;
	};
}