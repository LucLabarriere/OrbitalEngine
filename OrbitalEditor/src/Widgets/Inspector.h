#pragma once
#include "OrbitalEngine/Logic/Scene.h"
#include "OrbitalEngine/Logic/Entity.h"

using namespace Orbital;

class Inspector
{
public:
	Inspector(Ref<Scene>& scene);

	void render();
	void setEntity(const Entity& entity) { m_entity = entity; }

private:
	Ref<Scene> m_scene;
	Entity m_entity;
	inline static const char* m_layerRange[OE_LAST_LAYER + 1] = {
		"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16",
		"17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30", "31"
	};
};