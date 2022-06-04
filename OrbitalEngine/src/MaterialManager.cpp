#include "OrbitalEngine/Graphics.h"

namespace Orbital
{
	void MaterialManager::Initialize()
	{
		sInstance = new MaterialManager();
	}

	MaterialManager::MaterialManager()
		: AssetManager<Material>("MaterialManager")
	{
		Push(Material::Create("Blank", "Blank"));
		Push(Material::Create("Damier", "Damier"));
	}

	void MaterialManager::Push(Ref<Material>&& material)
	{
		mAssets.push_back(material);
		Renderer::PushBufferUnit(material, false);
	}

}