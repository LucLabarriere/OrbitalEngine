#pragma once

#include "OrbitalEngine/Graphics/Material.h"

namespace Orbital
{
	class MaterialManager : public AssetManager<Material>
	{
	public:
		static void Initialize() { s_instance = new MaterialManager(); }

	private:
		MaterialManager()
		{
			s_managerName = "MaterialManager";
			m_assets.push_back(Material::Create("Blank", "Blank"));
			m_assets.push_back(Material::Create("Damier", "Damier"));
		}
	};
}
