#include "OrbitalEngine/Graphics/ShaderManager.h"
#include "OrbitalEngine/Graphics/Shader.h"

namespace Orbital
{
	ShaderManager::ShaderManager()
	{
		load("Base", "shaders/Base.glsl");
		load("PostProcess", "shaders/PostProcess.glsl");
	}

	Ref<Shader>& ShaderManager::load(const std::string& shaderName, const std::string& shaderPath)
    {
		size_t id = m_shaders.size();
		
		for (const auto& shader : m_shaders)
			OE_ASSERT(shader->getName() != shaderName, "ShaderManager: {} is already loaded", shaderName);

		Ref<Shader> shader(Shader::Create(id, shaderName, Settings::GetAssetPath(shaderPath)));

		m_shaders.push_back(shader);

		return m_shaders[id];
    }

	const Ref<Shader>& ShaderManager::getShader(size_t id) const
	{
		return m_shaders[id];
	}

	const Ref<Shader>& ShaderManager::getShader(const std::string& shaderName) const
	{
		for (const auto& shader : m_shaders)
			if (shader->getName() == shaderName)
				return shader;

		OE_RAISE_SIGSEGV("ShaderManager: {} is not stored in the ShaderManager", shaderName);
		return m_shaders[0];
	}

}