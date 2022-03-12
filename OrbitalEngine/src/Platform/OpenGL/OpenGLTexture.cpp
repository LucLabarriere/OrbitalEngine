#include "OpenGLTexture.h"

namespace OrbitalEngine
{
	Texture* Texture::Create(
		const std::string& name, unsigned int width, unsigned int height, unsigned char* data)
	{
		return new OpenGLTexture(name, width, height, data);
	}

	Texture* Texture::Create(const std::string& name, TextureData texData)
	{
		return new OpenGLTexture(name, texData.width, texData.height, texData.data);
	}

	OpenGLTexture::OpenGLTexture(const std::string& name, unsigned int width, unsigned int height, unsigned char* data)
		: Texture(name, width, height)
	{
		glActiveTexture(GL_TEXTURE0);
		glad_glGenTextures(1, &m_rendererId);
		bind();

		glad_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glad_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glad_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glad_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glad_glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glad_glGenerateMipmap(GL_TEXTURE_2D);
	}

	OpenGLTexture::~OpenGLTexture()
	{
		glad_glDeleteTextures(1, &m_rendererId);
	}

	void OpenGLTexture::bind() const
	{
		glActiveTexture(GL_TEXTURE0);
		glad_glBindTexture(GL_TEXTURE_2D, m_rendererId);
	}

	void OpenGLTexture::unbind() const
	{
		glad_glBindTexture(GL_TEXTURE_2D, 0);
	}
}