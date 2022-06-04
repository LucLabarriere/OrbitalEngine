#pragma once
#include "OrbitalEngine/Graphics/Texture.h"

namespace Orbital
{
	class OpenGLTexture: public Texture
	{
	public:
		virtual ~OpenGLTexture() override;

		virtual void Bind() const override;
		virtual void Bind(unsigned int slot) const override;
		virtual void Unbind() const override;

		virtual void SetWrapS(unsigned int value) override;
		virtual void SetWrapT(unsigned int value) override;
		virtual void SetMinFilter(unsigned int value) override;
		virtual void SetMagFilter(unsigned int value) override;

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