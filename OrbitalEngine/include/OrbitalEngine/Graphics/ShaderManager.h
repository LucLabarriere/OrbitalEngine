#pragma once

#include "OrbitalEngine/Graphics/Shader.h"
#include "OrbitalEngine/Utils.h"

namespace Orbital
{
	class ShaderManager : public AssetManager<Shader>
	{
	public:
		static void Initialize() { sInstance = new ShaderManager(); }
		static void ReloadShaders() { ((ShaderManager*)sInstance)->ReloadShadersImpl(); }

	private:
		ShaderManager();
		WeakRef<Shader> Load(const std::string& tag, const std::string& shaderPath);
		void ReloadShadersImpl();
	};
}
