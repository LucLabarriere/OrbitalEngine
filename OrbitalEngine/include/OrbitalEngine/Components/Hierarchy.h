#pragma once

#include "OrbitalEngine/Utils/Misc.h"
#include "OrbitalEngine/Logic/Entity.h"

namespace Orbital
{
	class Scene;

	namespace Components
	{
		class Hierarchy
		{
		public:
			Hierarchy(Ref<Scene>& scene, const Entity& entity);
			~Hierarchy();

			void setParent(const Entity& parent);
			void removeChild(const Entity& entity);

			const Entity& getParent() const;
			const std::vector<Entity>& getChildren() const;

			std::vector<Entity>::iterator begin();
			std::vector<Entity>::iterator end();

		private:
			void addChild(const Entity& child);

			std::weak_ptr<Scene> m_scene;
			Entity* m_parent;
			Entity m_entity;
			std::vector<Entity> m_children;
		};
	}
}