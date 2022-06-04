#pragma once

#include "OrbitalEngine/Utils.h"

namespace Orbital
{
	class ShaderManager;

	class Shader : public Asset
	{
	public:
		virtual ~Shader() {};

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetUniform1i(const std::string& name, int value) const = 0;
		virtual void SetUniform1f(const std::string& name, float value) const = 0;
		virtual void SetUniform2f(const std::string& name, const glm::vec2& value) const = 0;
		virtual void SetUniform2f(const std::string& name, float v1, float v2) const = 0;
		virtual void SetUniform3f(const std::string& name, const glm::vec3& value) const = 0;
		virtual void SetUniform3f(const std::string& name, float v1, float v2, float v3) const = 0;
		virtual void SetUniform4f(const std::string& name, const glm::vec4& value) const = 0;
		virtual void SetUniform4f(const std::string& name, float v1, float v2, float v3, float v4) const = 0;
		virtual void SetUniformMat4f(const std::string& name, const glm::mat4& value) const = 0;

		const std::string& GetContent() const { return mContent; }
		const std::string& GetFilePath() const { return mFilepath; }

	protected:
		Shader(const std::string& name, const std::string& filepath)
			: Asset(sId, name), mRendererId(0), mFilepath(filepath) { sId += 1; }
		static Shader* Create(const std::string& name, const std::string& filepath);
		virtual void Reload() = 0;

	protected:
		friend ShaderManager;

		unsigned int mRendererId;
		std::string mFilepath;
		std::string mContent = "";

		static inline size_t sId = 0;
	};
}