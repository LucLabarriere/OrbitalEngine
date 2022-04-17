#pragma once

#include "OrbitalEngine/Utils.h"
namespace 
	Orbital
{
	class ShaderManager;

	class Shader : public Asset
	{
	public:
		virtual ~Shader() {};

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void setUniform1i(const std::string& name, int value) const = 0;
		virtual void setUniform1f(const std::string& name, float value) const = 0;
		virtual void setUniform2f(const std::string& name, const glm::vec2& value) const = 0;
		virtual void setUniform2f(const std::string& name, float v1, float v2) const = 0;
		virtual void setUniform3f(const std::string& name, const glm::vec3& value) const = 0;
		virtual void setUniform3f(const std::string& name, float v1, float v2, float v3) const = 0;
		virtual void setUniform4f(const std::string& name, const glm::vec4& value) const = 0;
		virtual void setUniform4f(const std::string& name, float v1, float v2, float v3, float v4) const = 0;
		virtual void setUniformMat4f(const std::string& name, const glm::mat4& value) const = 0;

		const std::string& getContent() const { return m_content; }

	protected:
		Shader(const std::string& name, const std::string& filepath)
			: Asset(name), m_rendererId(0), m_filepath(filepath) { };
		static Shader* Create(const std::string& name, const std::string& filepath);

	protected:
		friend ShaderManager;

		unsigned int m_rendererId;
		std::string m_filepath;
		std::string m_content = "";
	};
}