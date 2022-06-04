#pragma once

#include "OrbitalEngine/Graphics/Shader.h"

namespace Orbital
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

		void Bind() const override;
		void Unbind() const override;

		void SetUniform1i(const std::string& name, int value) const override;
		void SetUniform1f(const std::string& name, float value) const override;
		void SetUniform2f(const std::string& name, const glm::vec2& v) const override;
		void SetUniform2f(const std::string& name, float v1, float v2) const override;
		void SetUniform3f(const std::string& name, const glm::vec3& v) const override;
		void SetUniform3f(const std::string& name, float v1, float v2, float v3) const override;
		void SetUniform4f(const std::string& name, const glm::vec4& v) const override;
		void SetUniform4f(const std::string& name, float v1, float v2, float v3, float v4) const override;
		void SetUniformMat4f(const std::string& name, const glm::mat4& value) const override;

	private:
		OpenGLShader(const std::string& tag, const std::string& filepath);

		unsigned int getUniformLocation(const std::string& name) const;
		void createShader(const std::string& vertexShader, const std::string& fragmentShader);
		unsigned int compileShader(unsigned int type, const std::string& source);
		Sources parseSourceCode(const std::string& filepath);
		virtual void Reload();

	private:
		friend Shader;
	};
}