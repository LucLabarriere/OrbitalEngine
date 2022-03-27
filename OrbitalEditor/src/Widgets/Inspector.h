#pragma once
#include "OrbitalEngine/Logic/Scene.h"
#include "OrbitalEngine/Logic/Entity.h"

using namespace OrbitalEngine;

class Inspector
{
public:
	Inspector(Ref<Scene>& scene);

	void render();
	void setEntity(const Entity& entity) { m_entity = entity; }

private:
	Ref<Scene> m_scene;
	Entity m_entity;
};