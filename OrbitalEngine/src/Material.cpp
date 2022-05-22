#include "OrbitalEngine/Graphics/Material.h"
#include "OrbitalEngine/Graphics/TextureManager.h"
#include "OrbitalEngine/Graphics/ShaderManager.h"

namespace Orbital
{
	void Material::bind() const
	{
		this;
		auto shader = m_shader.lock();
		shader->bind();
		m_diffuseMap->bind(0);
		m_specularMap->bind(1);
		shader->setUniform1i("u_Material.DiffuseMap", 0);
		shader->setUniform3f("u_Material.DiffuseTint", m_diffuseTint);
		shader->setUniform1i("u_Material.SpecularMap", 1);
		shader->setUniform3f("u_Material.SpecularTint", m_specularTint);
		shader->setUniform1f("u_Material.Shininess", m_shininess);
		shader->setUniform1f("u_Material.Ambient", m_ambient);
	}

	Material::Material(const std::string& tag)
		: Asset(s_id, tag)
	{
		s_id += 1;
		m_diffuseMap = TextureManager::Get(0).lock();
		m_specularMap = TextureManager::Get(0).lock();
		m_shader = ShaderManager::Get(0);
	}

	Material::Material(const std::string& tag, const std::string& diffuseMapName)
		: Asset(s_id, tag)
	{
		s_id += 1;
		m_diffuseMap = TextureManager::Get(diffuseMapName).lock();
		m_specularMap = TextureManager::Get(0).lock();
		m_shader = ShaderManager::Get(0);
	}

	Material::Material(const std::string& tag, const std::string& diffuseMapName, const std::string& specularMapName)
		: Asset(s_id, tag)
	{
		s_id += 1;
		m_diffuseMap = TextureManager::Get(diffuseMapName).lock();
		m_specularMap = TextureManager::Get(specularMapName).lock();
		m_shader = ShaderManager::Get(0);
	}

	WeakRef<Shader> Material::getShader() const
	{
		return m_shader;
	}
}