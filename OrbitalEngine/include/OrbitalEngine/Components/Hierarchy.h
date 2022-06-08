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
		Hierarchy();
		Hierarchy(const Entity& entity, const Entity& parent);
		~Hierarchy();

		void SetEntity(const Entity& entity);
		void SetParent(const Entity& parent);
		void SetParent(const UUID& uuid);
		void RemoveChild(const Entity& entity);

		Entity& GetParent();
		const Entity& GetParent() const;
		std::vector<Entity>& GetChildren();
		const std::vector<Entity>& GetChildren() const;

		std::vector<Entity>::iterator begin();
		std::vector<Entity>::iterator end();

	private:
		void AddChild(const Entity& child);

		Entity mParent;
		Entity mEntity;
		std::vector<Entity> mChildren;
	};
}

namespace YAML
{
	template<>
	struct convert<Orbital::Hierarchy>
	{
		static Node encode(const Orbital::Hierarchy& hierarchy)
		{
			Node node;
			auto& parent = hierarchy.GetParent();

			if (parent.IsValid())
				return Node(parent.GetComponent<Orbital::UUID>().ToString());
			else
				return Node("None");
		}

		static bool decode(const Node& node, Orbital::Hierarchy& hierarchy)
		{
			auto parent = node.as<std::string>();

			if (parent == "None")
				hierarchy.SetParent(Orbital::Entity());
			else
				hierarchy.SetParent(Orbital::Entity::FromUUID(Orbital::UUID::FromString(parent)));

			return true;
		}
	};
}