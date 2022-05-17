#include "OpenGLShader.h"

namespace Orbital
{
	Shader* Shader::Create(const std::string& tag, const std::string& filepath)
	{
		Logger::Debug("OpenGLShader: Creating shader: {}", tag);
		return new OpenGLShader(tag, filepath);
	}

	OpenGLShader::~OpenGLShader()
	{
		unbind();
		glad_glDeleteProgram(m_rendererId);
	}

	void OpenGLShader::bind() const
	{
		glad_glUseProgram(m_rendererId);
	}

	void OpenGLShader::unbind() const
	{
		glad_glUseProgram(0);
	}

	void OpenGLShader::setUniform1i(const std::string& name, int value) const
	{
		unsigned int location = getUniformLocation(name);
		glad_glUniform1i(location, value);
	}

	void OpenGLShader::setUniform1f(const std::string& name, float value) const
	{
		unsigned int location = getUniformLocation(name);
		glad_glUniform1f(location, value);
	}

	void OpenGLShader::setUniform2f(const std::string& name, const glm::vec2& v) const
	{
		unsigned int location = getUniformLocation(name);
		glad_glUniform2f(location, v[0], v[1]);
	}

	void OpenGLShader::setUniform2f(const std::string& name, float v1, float v2) const
	{
		unsigned int location = getUniformLocation(name);
		glad_glUniform2f(location, v1, v2);
	}

	void OpenGLShader::setUniform3f(const std::string& name, const glm::vec3& v) const
	{
		unsigned int location = getUniformLocation(name);
		glad_glUniform3f(location, v[0], v[1], v[2]);
	}

	void OpenGLShader::setUniform3f(const std::string& name, float v1, float v2, float v3) const
	{
		unsigned int location = getUniformLocation(name);
		glad_glUniform3f(location, v1, v2, v3);
	}

	void OpenGLShader::setUniform4f(const std::string& name, const glm::vec4& v) const
	{
		unsigned int location = getUniformLocation(name);
		glad_glUniform4f(location, v[0], v[1], v[2], v[3]);
	}

	void OpenGLShader::setUniform4f(const std::string& name, float v1, float v2, float v3, float v4) const
	{
		unsigned int location = getUniformLocation(name);
		glad_glUniform4f(location, v1, v2, v3, v4);
	}

	void OpenGLShader::setUniformMat4f(const std::string& name, const glm::mat4& value) const
	{
		unsigned int location = getUniformLocation(name);
		glad_glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
	}

	OpenGLShader::OpenGLShader(const std::string& tag, const std::string& filepath)
		: Shader(tag, filepath)
	{
		Sources sources = parseSourceCode(m_filepath);
		m_content = "#Vertex Shader\n" + sources.vs + "\n#Fragment Shader\n" + sources.fs;

		createShader(sources.vs, sources.fs);
	}

	unsigned int OpenGLShader::getUniformLocation(const std::string& name) const
	{
		int location = glad_glGetUniformLocation(m_rendererId, name.c_str());

		if (location == -1)
			Logger::Error("OpenGLShader: In shader '{}' Uniform '{}' doesn't exist", m_tag, name);

		return location;
	}

	void OpenGLShader::createShader(const std::string& vertexShader, const std::string& fragmentShader)
	{
		unsigned int vs = this->compileShader(GL_VERTEX_SHADER, vertexShader);
		unsigned int fs = this->compileShader(GL_FRAGMENT_SHADER, fragmentShader);

		m_rendererId = glad_glCreateProgram();
		glad_glAttachShader(m_rendererId, vs);
		glad_glAttachShader(m_rendererId, fs);

		glad_glLinkProgram(m_rendererId);
		glad_glValidateProgram(m_rendererId);

		glad_glDeleteShader(vs);
		glad_glDeleteShader(fs);
	}

	unsigned int OpenGLShader::compileShader(unsigned int type, const std::string& source)
	{
		const char* cSource = source.c_str();

		GLint compile_ok = GL_FALSE;
		unsigned int shader = glad_glCreateShader(type);
		glad_glShaderSource(shader, 1, &cSource, nullptr);
		glad_glCompileShader(shader);
		glad_glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_ok);

		const std::string typeName = (type == GL_VERTEX_SHADER) ? "Vertex shader" : "Fragment shader";

		if (!compile_ok)
		{
			GLint maxLength = 0;
			glad_glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
			std::vector<GLchar> errorLog(maxLength);
			glad_glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);
			glad_glDeleteShader(shader);

			Logger::Error("OpenGLShader: Error in shader '{}' ({}) : {}", m_tag, typeName, errorLog);
			return 0;
		}
		
		return shader;
	}

	OpenGLShader::Sources OpenGLShader::parseSourceCode(const std::string& filepath)
	{
		std::ifstream sourceFile;
		Logger::Debug("Loading shader: '{}'", filepath);
		OE_ASSERT(fileExists(filepath), "OpenGLShader: '{}': no such file", filepath);

		sourceFile.open(filepath, std::ios::out);

		std::string line;
		std::string vs;
		std::string fs;
		std::string* current = &vs;

		while (std::getline(sourceFile, line))
		{
			if (line == "// Vertex shader")
				current = &vs;
			else if (line == "// Fragment shader")
				current = &fs;
			else
			{
				current->append(line + '\n');
			}
		}
		sourceFile.close();

		return { vs, fs };
	}

	void OpenGLShader::reload()
	{
		unbind();
		glad_glDeleteProgram(m_rendererId);

		Sources sources = parseSourceCode(m_filepath);
		m_content = "#Vertex Shader\n" + sources.vs + "\n#Fragment Shader\n" + sources.fs;

		createShader(sources.vs, sources.fs);
	}
}
