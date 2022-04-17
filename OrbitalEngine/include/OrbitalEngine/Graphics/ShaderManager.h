#pragma once

#include "OrbitalEngine/Graphics/Shader.h"
#include "OrbitalEngine/Utils.h"

namespace Orbital
{
	class ShaderManager : public AssetManager<Shader>
	{
	public:
		static void Initialize() { s_instance = new ShaderManager(); }

	private:
		ShaderManager();
		WeakRef<Shader> load(const std::string& tag, const std::string& shaderPath);

		const WeakRef<Shader> get(size_t id) const;
		const WeakRef<Shader> get(const std::string& tag) const;
	};
}
