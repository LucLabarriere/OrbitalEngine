#include "OrbitalEngine/Graphics.h"

namespace Orbital
{
	void MaterialManager::Initialize()
	{
		s_instance = new MaterialManager();
	}

	MaterialManager::MaterialManager()
	{
		s_managerName = "MaterialManager";
		push(Material::Create("Blank", "Blank"));
		push(Material::Create("Damier", "Damier"));
	}

	void MaterialManager::push(Ref<Material>&& material)
	{
		m_assets.push_back(material);
		Renderer::PushBufferUnit(material, false);
	}

}