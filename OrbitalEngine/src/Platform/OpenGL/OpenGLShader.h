#pragma once

#include "OrbitalEngine/Shader.h"

namespace OrbitalEngine
{
	class OpenGLShader : public Shader
	{
	public:
		struct Sources
		{
			std::string vs;
			std::string fs;
		};

	public:
		virtual ~OpenGLShader();

		void bind() const override;
		void unbind() const override;

		void setUniform1i(const std::string& name, int value) const override;
		void setUniform1f(const std::string& name, float value) const override;
		void setUniform2f(const std::string& name, const glm::vec2& v) const override;
		void setUniform2f(const std::string& name, float v1, float v2) const override;
		void setUniform3f(const std::string& name, const glm::vec3& v) const override;
		void setUniform3f(const std::string& name, float v1, float v2, float v3) const override;
		void setUniform4f(const std::string& name, const glm::vec4& v) const override;
		void setUniform4f(const std::string& name, float v1, float v2, float v3, float v4) const override;
		void setUniformMat4f(const std::string& name, const glm::mat4& value) const override;

	private:
		OpenGLShader(unsigned int shaderId, const std::string& name, const std::string& filepath);

		unsigned int getUniformLocation(const std::string& name) const;
		void createShader(const std::string& vertexShader, const std::string& fragmentShader);
		unsigned int compileShader(unsigned int type, const std::string& source);
		Sources parseSourceCode(const std::string& filepath);

	private:
		friend Shader;
	};
}