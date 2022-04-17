#include "OpenGLTexture.h"
#include "vendor/stb_image.h"

namespace Orbital
{
	Texture* Texture::Create(
		const std::string& tag, unsigned int width, unsigned int height, unsigned char* data)
	{
		return new OpenGLTexture(tag, width, height, data);
	}

	Texture* Texture::Create(const std::string& tag, TextureData texData)
	{
		return new OpenGLTexture(tag, texData.width, texData.height, texData.data, texData.internalFormat, texData.format);
	}

	TextureData Texture::Load(const std::string& filename)
	{
		TextureData data;
		OE_ASSERT(fileExists(filename), "Texture: '{}' does not exist.", filename);
		data.data = stbi_load(
			filename.c_str(), &data.width, &data.height, &data.nChannels, 0);

		return data;
	}

	OpenGLTexture::OpenGLTexture(
		const std::string& tag, unsigned int width, unsigned int height,
		unsigned char* data, unsigned int internalFormat, unsigned int format)
		: Texture(tag, width, height)
	{
		glActiveTexture(GL_TEXTURE0);
		glad_glGenTextures(1, &m_rendererId);
		bind();

		glad_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glad_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glad_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glad_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glad_glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, data);
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

	void OpenGLTexture::bind(unsigned int slot) const
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glad_glBindTexture(GL_TEXTURE_2D, m_rendererId);
	}

	void OpenGLTexture::unbind() const
	{
		glad_glBindTexture(GL_TEXTURE_2D, 0);
	}
}