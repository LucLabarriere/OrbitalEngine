#pragma once
#include "OrbitalEngine/Logic/Scene.h"
#include "OrbitalEngine/Graphics.h"
#include "Widget.h"

using namespace Orbital;

enum class InspectedObjectTag
{
	None = 0,
	Entity,
	Texture,
	Text,
	Material
};

struct InspectedObject
{
	InspectedObjectTag Tag = InspectedObjectTag::Entity;
	std::variant<
		bool,
		Entity,
		WeakRef<Texture>,
		std::string,
		WeakRef<Material>
	> Value = Entity();
};

class Inspector : public Widget
{
public:

public:
	static inline void Initialize() { s_instance = new Inspector(); }
	static inline void Render() { s_instance->render(); };

	static inline void SetEntity(const Entity& entity)
	{ 
		s_instance->m_object.Value = entity;
		s_instance->m_object.Tag = InspectedObjectTag::Entity;
	}
	static inline void SetTexture(WeakRef<Texture> texture)
	{
		s_instance->m_object.Value = texture;
		s_instance->m_object.Tag = InspectedObjectTag::Texture;
	}
	static inline void SetText(const std::string& text)
	{
		s_instance->m_object.Value = text;
		s_instance->m_object.Tag = InspectedObjectTag::Text;
	}
	static inline void SetMaterial(WeakRef<Material> material)
	{
		s_instance->m_object.Value = material;
		s_instance->m_object.Tag = InspectedObjectTag::Material;
	}

	static const InspectedObject& GetInspectedObject() { return s_instance->m_object; }

private:
	Inspector();

	void render();
	void renderEntity();
	void renderTexture();
	void renderText();
	void renderMaterial();

private:
	static inline Inspector* s_instance = nullptr;
	
	InspectedObject m_object;
	inline static const char* m_layerRange[OE_LAST_LAYER + 1] = {
		"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16",
		"17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30", "31"
	};
};