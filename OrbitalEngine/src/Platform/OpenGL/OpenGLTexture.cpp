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
		OE_ASSERT(FileExists(filename), "Texture: '{}' does not exist.", filename);
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
		glad_glGenTextures(1, &mRendererId);
		glad_glGenSamplers(1, &m_samplerId);
		Bind();

		SetWrapS(GL_REPEAT);
		SetWrapT(GL_REPEAT);
		SetMinFilter(GL_LINEAR);
		SetMagFilter(GL_LINEAR);

		glad_glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, mWidth, mHeight, 0, format, GL_UNSIGNED_BYTE, data);
		glad_glGenerateMipmap(GL_TEXTURE_2D);
	}

	OpenGLTexture::~OpenGLTexture()
	{
		glad_glDeleteTextures(1, &mRendererId);
		glad_glDeleteSamplers(1, &m_samplerId);
	}

	void OpenGLTexture::Bind() const
	{
		glad_glActiveTexture(GL_TEXTURE0);
		glad_glBindTexture(GL_TEXTURE_2D, mRendererId);
		glad_glBindSampler(0, m_samplerId);
	}

	void OpenGLTexture::Bind(unsigned int slot) const
	{
		glad_glActiveTexture(GL_TEXTURE0 + slot);
		glad_glBindTexture(GL_TEXTURE_2D, mRendererId);
		glad_glBindSampler(slot, m_samplerId);
	}

	void OpenGLTexture::Unbind() const
	{
		glad_glBindTexture(GL_TEXTURE_2D, 0);
		glad_glBindSampler(0, 0);
	}

	void OpenGLTexture::SetWrapS(unsigned int value)
	{
		Bind();
		mWrapS = value;
		glad_glSamplerParameteri(m_samplerId, GL_TEXTURE_WRAP_S, value);
	}

	void OpenGLTexture::SetWrapT(unsigned int value)
	{
		Bind();
		mWrapT = value;
		glad_glSamplerParameteri(m_samplerId, GL_TEXTURE_WRAP_T, value);
	}

	void OpenGLTexture::SetMinFilter(unsigned int value)
	{
		Bind();
		mMinFilter = value;
		glad_glSamplerParameteri(m_samplerId, GL_TEXTURE_MIN_FILTER, value);
	}

	void OpenGLTexture::SetMagFilter(unsigned int value)
	{
		Bind();
		mMagFilter = value;
		glad_glSamplerParameteri(m_samplerId, GL_TEXTURE_MAG_FILTER, value);
	}
}