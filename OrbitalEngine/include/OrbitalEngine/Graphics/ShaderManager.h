#pragma once

#include "OrbitalEngine/Graphics/Shader.h"
#include "OrbitalEngine/Utils.h"

namespace Orbital
{
	class ShaderManager
	{
	public:
		inline static void Initialize()
		{
			s_instance = new ShaderManager();
		}

		inline static void Terminate()
		{
			delete s_instance;
		}

		inline static const Ref<Shader>& GetShader(size_t id) { return s_instance->getShader(id); }
		inline static const Ref<Shader>& GetShader(const std::string& shaderName) { return s_instance->getShader(shaderName); };

	private:
		ShaderManager();
		Ref<Shader>& load(const std::string& shaderName, const std::string& shaderPath);

		const Ref<Shader>& getShader(size_t id) const;
		const Ref<Shader>& getShader(const std::string& shaderName) const;
		
	private:
		inline static ShaderManager* s_instance = nullptr;
		std::vector<Ref<Shader>> m_shaders;
	};
}
