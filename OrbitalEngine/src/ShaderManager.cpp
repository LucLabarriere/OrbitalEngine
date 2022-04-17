#include "OrbitalEngine/Graphics/ShaderManager.h"
#include "OrbitalEngine/Graphics/Shader.h"

namespace Orbital
{
	ShaderManager::ShaderManager() : AssetManager<Shader>()
	{
		s_managerName = "ShaderManager";
		load("Base", "shaders/Base.glsl");
		load("PostProcess", "shaders/PostProcess.glsl");
	}

	WeakRef<Shader> ShaderManager::load(const std::string& tag, const std::string& shaderPath)
    {
		for (const auto& shader : m_assets)
			OE_ASSERT(shader->getTag() != tag, "ShaderManager: {} is already loaded", tag);

		Ref<Shader> shader(Shader::Create(tag, Settings::GetAssetPath(shaderPath)));
		m_assets.push_back(shader);

		return shader;
    }

	const WeakRef<Shader> ShaderManager::get(size_t id) const
	{
		for (const auto& shader : m_assets)
			if (shader->getId() == id)
				return shader;

		OE_RAISE_SIGSEGV("ShaderManager: {} is not stored in the ShaderManager", id);
	}

	const WeakRef<Shader> ShaderManager::get(const std::string& tag) const
	{
		for (const auto& shader : m_assets)
			if (shader->getTag() == tag)
				return shader;

		OE_RAISE_SIGSEGV("ShaderManager: {} is not stored in the ShaderManager", tag);
	}
}


