#pragma once
#include "OrbitalEngine/Logic/Scene.h"
#include "OrbitalEngine/Logic/Entity.h"
#include "OrbitalEngine/Graphics/Texture.h"

using namespace Orbital;

enum class InspectedObjectTag
{
	Entity = 0,
	Texture,
	Text
};

class Inspector
{
private:
	struct InspectedObject
	{
		InspectedObjectTag Tag = InspectedObjectTag::Entity;
		std::variant<
			Entity,
			Ref<Texture>,
			std::string
		> Value = Entity();
	};

public:
	static inline void Initialize(Ref<Scene>& scene) { s_instance = new Inspector(scene); }
	static inline void Render() { s_instance->render(); };

	static inline void SetEntity(const Entity& entity)
	{ 
		s_instance->m_object.Value = entity;
		s_instance->m_object.Tag = InspectedObjectTag::Entity;
	}
	static inline void SetTexture(const Ref<Texture>& texture)
	{
		s_instance->m_object.Value = texture;
		s_instance->m_object.Tag = InspectedObjectTag::Texture;
	}
	static inline void SetText(const std::string& text)
	{
		s_instance->m_object.Value = text;
		s_instance->m_object.Tag = InspectedObjectTag::Text;
	}

private:
	Inspector(Ref<Scene>& scene);

	void render();
	void renderEntity();
	void renderTexture();
	void renderText();

private:
	static inline Inspector* s_instance = nullptr;

	Ref<Scene> m_scene;
	InspectedObject m_object;
	inline static const char* m_layerRange[OE_LAST_LAYER + 1] = {
		"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16",
		"17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30", "31"
	};
};