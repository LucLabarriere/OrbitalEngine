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
	static inline void Initialize() { sInstance = new Inspector(); }
	static inline void Render() { sInstance->RenderImpl(); };

	static inline void SetEntity(const Entity& entity)
	{ 
		sInstance->mObject.Value = entity;
		sInstance->mObject.Tag = InspectedObjectTag::Entity;
	}
	static inline void SetTexture(WeakRef<Texture> texture)
	{
		sInstance->mObject.Value = texture;
		sInstance->mObject.Tag = InspectedObjectTag::Texture;
	}
	static inline void SetText(const std::string& text)
	{
		sInstance->mObject.Value = text;
		sInstance->mObject.Tag = InspectedObjectTag::Text;
	}
	static inline void SetMaterial(WeakRef<Material> material)
	{
		sInstance->mObject.Value = material;
		sInstance->mObject.Tag = InspectedObjectTag::Material;
	}

	static const InspectedObject& GetInspectedObject() { return sInstance->mObject; }

private:
	Inspector();

	void RenderImpl();
	void RenderEntity();
	void RenderTexture();
	void RenderText();
	void RenderMaterial();

private:
	static inline Inspector* sInstance = nullptr;
	
	InspectedObject mObject;
	inline static const char* mLayerRange[OE_LAST_LAYER + 1] = {
		"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16",
		"17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30", "31"
	};
};