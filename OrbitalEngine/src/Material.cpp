#include "OrbitalEngine/Graphics/Material.h"
#include "OrbitalEngine/Graphics/TextureManager.h"
#include "OrbitalEngine/Graphics/ShaderManager.h"

namespace Orbital
{
	void Material::bind()
	{

	}

	Material::Material(const std::string& tag)
		: Asset(tag)
	{
		m_diffuseMapId = TextureManager::Get(0);
		m_shader = ShaderManager::Get(0);
	}

	Material::Material(const std::string& tag, const std::string& diffuseMapName)
		: Asset(tag)
	{
		m_diffuseMapId = TextureManager::Get(diffuseMapName);
		m_shader = ShaderManager::Get(0);
	}
}