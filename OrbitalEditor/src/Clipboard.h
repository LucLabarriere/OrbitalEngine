#pragma once
#include "Widgets/Inspector.h"
#include "OrbitalEngine/Graphics.h"
#include "OrbitalEngine/Utils.h"
#include "Widgets/Widget.h"

class Clipboard : public Widget
{
public:
	static void Initialize() { s_instance = new Clipboard(); };
	static void Copy(const InspectedObject& object)
	{
		s_instance->m_object.Tag = object.Tag;
		s_instance->m_object.Value = object.Value;
	}

	static void Paste()
	{
		if (s_instance->m_object.Tag == InspectedObjectTag::Entity)
		{
			(*s_instance->sActiveScene)->DuplicateEntity(std::get<Entity>(s_instance->m_object.Value));
		}
	};

private:
	Clipboard() : m_object()
	{
		m_object.Tag = InspectedObjectTag::None; m_object.Value = false;
	}

private:
	static inline Clipboard* s_instance = nullptr;

	InspectedObject m_object;

};