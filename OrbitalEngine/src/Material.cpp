#include "OrbitalEngine/Graphics/Material.h"
#include "OrbitalEngine/Graphics/TextureManager.h"
#include "OrbitalEngine/Graphics/ShaderManager.h"

namespace Orbital
{
	void Material::bind() const
	{
		m_diffuseMap->bind(0);
		m_specularMap->bind(1);

		m_shader->bind();
		m_shader->setUniform1f("u_Material.Ambient", m_ambient);
		m_shader->setUniform1i("u_Material.DiffuseMap", m_diffuseMap->getRendererId());
		m_shader->setUniform3f("u_Material.DiffuseTint", m_diffuseTint);
		m_shader->setUniform1i("u_Material.SpecularMap", m_specularMap->getRendererId());
		m_shader->setUniform3f("u_Material.SpecularTint", m_specularTint);
		m_shader->setUniform1f("u_Material.Shininess", m_shininess);
	}

	Material::Material(const std::string& tag)
		: Asset(s_id, tag)
	{
		s_id += 1;
		m_diffuseMap = TextureManager::Get(0).lock();
		m_specularMap = TextureManager::Get(0).lock();
		m_shader = ShaderManager::Get(0).lock();
	}

	Material::Material(const std::string& tag, const std::string& diffuseMapName)
		: Asset(s_id, tag)
	{
		s_id += 1;
		m_diffuseMap = TextureManager::Get(diffuseMapName).lock();
		m_specularMap = TextureManager::Get(0).lock();
		m_shader = ShaderManager::Get(0).lock();
	}

	Material::Material(const std::string& tag, const std::string& diffuseMapName, const std::string& specularMapName)
		: Asset(s_id, tag)
	{
		s_id += 1;
		m_diffuseMap = TextureManager::Get(diffuseMapName).lock();
		m_specularMap = TextureManager::Get(specularMapName).lock();
		m_shader = ShaderManager::Get(0).lock();
	}
}