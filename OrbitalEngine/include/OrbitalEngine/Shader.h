#pragma once

#include "OrbitalEngine/Context.h"
#include "OrbitalEngine/Tools.h"

namespace OrbitalEngine
{
	class Application;

	class ORBITAL_API Shader
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

	protected:
		Shader(unsigned int shaderId, const std::string& name, const std::string& filepath)
			: m_rendererId(0), m_shaderId(shaderId), m_name(name), m_filepath(filepath) { };
		static Shader* Create(unsigned int shaderId, const std::string& name, const std::string& filepath);

	protected:
		friend Application;

		unsigned int m_rendererId;
		unsigned int m_shaderId;
		std::string m_name;
		std::string m_filepath;
	};
}
