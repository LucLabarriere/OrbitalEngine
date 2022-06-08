#pragma once
#include "Widgets/Inspector.h"
#include "OrbitalEngine/Graphics.h"
#include "OrbitalEngine/Utils.h"
#include "Widgets/Widget.h"

class Clipboard
{
public:
	static void Initialize() { sInstance = new Clipboard(); };
	static void Copy(const InspectedObject& object)
	{
		sInstance->mObject.Tag = object.Tag;
		sInstance->mObject.Value = object.Value;
	}

	static void Paste()
	{
		if (sInstance->mObject.Tag == InspectedObjectTag::Entity)
		{
			OE::ActiveScene->DuplicateEntity(std::get<Entity>(sInstance->mObject.Value));
		}
	};

private:
	Clipboard() : mObject()
	{
		mObject.Tag = InspectedObjectTag::None; mObject.Value = false;
	}

private:
	static inline Clipboard* sInstance = nullptr;

	InspectedObject mObject;

};