#pragma once
#include "OrbitalEngine/Graphics/Texture.h"

namespace Orbital
{
	class OpenGLTexture: public Texture
	{
	public:
		virtual ~OpenGLTexture() override;

		virtual void bind() const override;
		virtual void bind(unsigned int slot) const override;
		virtual void unbind() const override;

		virtual void setWrapS(unsigned int value) override;
		virtual void setWrapT(unsigned int value) override;
		virtual void setMinFilter(unsigned int value) override;
		virtual void setMagFilter(unsigned int value) override;

	private:
		OpenGLTexture(
			const std::string& tag, unsigned int width,
			unsigned int height, unsigned char* data,
			unsigned int internalFormat = OE_RGB8,
			unsigned int format = OE_RGB);

	private:
		friend Texture;

		unsigned int m_samplerId;
	};
}