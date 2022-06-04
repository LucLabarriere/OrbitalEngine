#include "OrbitalEngine/Graphics/Material.h"
#include "OrbitalEngine/Graphics/TextureManager.h"
#include "OrbitalEngine/Graphics/ShaderManager.h"

namespace Orbital
{
	void Material::Bind() const
	{
		this;
		auto shader = mShader.lock();
		shader->Bind();
		mDiffuseMap->Bind(0);
		mSpecularMap->Bind(1);
		shader->SetUniform1i("u_Material.DiffuseMap", 0);
		shader->SetUniform3f("u_Material.DiffuseTint", mDiffuseTint);
		shader->SetUniform1i("u_Material.SpecularMap", 1);
		shader->SetUniform3f("u_Material.SpecularTint", mSpecularTint);
		shader->SetUniform1f("u_Material.Shininess", mShininess);
		shader->SetUniform1f("u_Material.Ambient", mAmbient);
	}

	Material::Material(const std::string& tag)
		: Asset(sId, tag)
	{
		sId += 1;
		mDiffuseMap = TextureManager::Get(0).lock();
		mSpecularMap = TextureManager::Get(0).lock();
		mShader = ShaderManager::Get(0);
	}

	Material::Material(const std::string& tag, const std::string& diffuseMapName)
		: Asset(sId, tag)
	{
		sId += 1;
		mDiffuseMap = TextureManager::Get(diffuseMapName).lock();
		mSpecularMap = TextureManager::Get(0).lock();
		mShader = ShaderManager::Get(0);
	}

	Material::Material(const std::string& tag, const std::string& diffuseMapName, const std::string& specularMapName)
		: Asset(sId, tag)
	{
		sId += 1;
		mDiffuseMap = TextureManager::Get(diffuseMapName).lock();
		mSpecularMap = TextureManager::Get(specularMapName).lock();
		mShader = ShaderManager::Get(0);
	}

	WeakRef<Shader> Material::GetShader() const
	{
		return mShader;
	}
}