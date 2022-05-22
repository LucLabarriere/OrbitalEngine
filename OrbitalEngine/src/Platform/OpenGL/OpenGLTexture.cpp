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
		glad_glGenSamplers(1, &m_samplerId);
		bind();

		setWrapS(GL_REPEAT);
		setWrapT(GL_REPEAT);
		setMinFilter(GL_LINEAR);
		setMagFilter(GL_LINEAR);

		glad_glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, data);
		glad_glGenerateMipmap(GL_TEXTURE_2D);
	}

	OpenGLTexture::~OpenGLTexture()
	{
		glad_glDeleteTextures(1, &m_rendererId);
		glad_glDeleteSamplers(1, &m_samplerId);
	}

	void OpenGLTexture::bind() const
	{
		glad_glActiveTexture(GL_TEXTURE0);
		glad_glBindTexture(GL_TEXTURE_2D, m_rendererId);
		glad_glBindSampler(0, m_samplerId);
	}

	void OpenGLTexture::bind(unsigned int slot) const
	{
		glad_glActiveTexture(GL_TEXTURE0 + slot);
		glad_glBindTexture(GL_TEXTURE_2D, m_rendererId);
		glad_glBindSampler(slot, m_samplerId);
	}

	void OpenGLTexture::unbind() const
	{
		glad_glBindTexture(GL_TEXTURE_2D, 0);
		glad_glBindSampler(0, 0);
	}

	void OpenGLTexture::setWrapS(unsigned int value)
	{
		bind();
		m_wrapS = value;
		glad_glSamplerParameteri(m_samplerId, GL_TEXTURE_WRAP_S, value);
	}

	void OpenGLTexture::setWrapT(unsigned int value)
	{
		bind();
		m_wrapT = value;
		glad_glSamplerParameteri(m_samplerId, GL_TEXTURE_WRAP_T, value);
	}

	void OpenGLTexture::setMinFilter(unsigned int value)
	{
		bind();
		m_minFilter = value;
		glad_glSamplerParameteri(m_samplerId, GL_TEXTURE_MIN_FILTER, value);
	}

	void OpenGLTexture::setMagFilter(unsigned int value)
	{
		bind();
		m_magFilter = value;
		glad_glSamplerParameteri(m_samplerId, GL_TEXTURE_MAG_FILTER, value);
	}
}