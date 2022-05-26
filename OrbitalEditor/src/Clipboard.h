#pragma once
#include "Widgets/Inspector.h"
#include "OrbitalEngine/Graphics.h"
#include "OrbitalEngine/Utils.h"

class Clipboard
{
public:
	static void Initialize(WeakRef<Scene> scene) { s_instance = new Clipboard(scene); };
	static void Copy(const InspectedObject& object)
	{
		s_instance->m_object.Tag = object.Tag;
		s_instance->m_object.Value = object.Value;
	}

	static void Paste()
	{
		if (s_instance->m_object.Tag == InspectedObjectTag::Entity)
		{
			s_instance->m_scene.lock()->duplicateEntity(std::get<Entity>(s_instance->m_object.Value));
		}
	};

private:
	Clipboard(WeakRef<Scene> scene) : m_scene(scene), m_object()
	{
		m_object.Tag = InspectedObjectTag::None; m_object.Value = false;
	}

private:
	static inline Clipboard* s_instance = nullptr;

	WeakRef<Scene> m_scene;
	InspectedObject m_object;

};