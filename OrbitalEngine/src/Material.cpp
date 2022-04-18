#include "OrbitalEngine/Graphics/Material.h"
#include "OrbitalEngine/Graphics/TextureManager.h"
#include "OrbitalEngine/Graphics/ShaderManager.h"

namespace Orbital
{
	void Material::bind() const
	{
		auto diffMap = m_diffuseMap.lock();
		auto specMap = m_specularMap.lock();

		diffMap->bind(0);
		specMap->bind(1);

		auto shader = m_shader.lock();
		shader->bind();
		shader->setUniform1f("u_Material.Ambient", m_ambient);
		shader->setUniform1i("u_Material.DiffuseMap", diffMap->getRendererId());
		shader->setUniform3f("u_Material.DiffuseTint", m_diffuseTint);
		shader->setUniform1i("u_Material.SpecularMap", specMap->getRendererId());
		shader->setUniform3f("u_Material.SpecularTint", m_specularTint);
		shader->setUniform1f("u_Material.Shininess", m_shininess);
	}

	Material::Material(const std::string& tag)
		: Asset(s_id, tag)
	{
		s_id += 1;
		m_diffuseMap = TextureManager::Get(0);
		m_specularMap = TextureManager::Get(0);
		m_shader = ShaderManager::Get(0);
	}

	Material::Material(const std::string& tag, const std::string& diffuseMapName)
		: Asset(s_id, tag)
	{
		s_id += 1;
		m_diffuseMap = TextureManager::Get(diffuseMapName);
		m_specularMap = TextureManager::Get(0);
		m_shader = ShaderManager::Get(0);
	}

	Material::Material(const std::string& tag, const std::string& diffuseMapName, const std::string& specularMapName)
		: Asset(s_id, tag)
	{
		s_id += 1;
		m_diffuseMap = TextureManager::Get(diffuseMapName);
		m_specularMap = TextureManager::Get(specularMapName);
		m_shader = ShaderManager::Get(0);
	}
}