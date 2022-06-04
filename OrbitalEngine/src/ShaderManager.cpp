#include "OrbitalEngine/Graphics/ShaderManager.h"
#include "OrbitalEngine/Graphics/Shader.h"

namespace Orbital
{
	ShaderManager::ShaderManager() : AssetManager<Shader>("ShaderManager")
	{
		Load("Base", "shaders/Base.glsl");
		Load("PostProcess", "shaders/PostProcess.glsl");
	}

	WeakRef<Shader> ShaderManager::Load(const std::string& tag, const std::string& shaderPath)
    {
		for (const auto& shader : mAssets)
			OE_ASSERT(shader->GetTag() != tag, "ShaderManager: {} is already loaded", tag);

		Ref<Shader> shader(Shader::Create(tag, Settings::GetAssetPath(shaderPath)));
		mAssets.push_back(shader);

		return shader;
    }

	void ShaderManager::ReloadShadersImpl()
	{
		for (auto& shader : mAssets)
		{
			shader->Reload();
		}
	}
}


