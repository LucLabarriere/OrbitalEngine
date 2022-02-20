#pragma once
#include "OrbitalEngine/Graphics/Texture.h"

namespace OrbitalEngine
{
	class OpenGLTexture: public Texture
	{
	public:
		virtual ~OpenGLTexture() override;

		virtual void bind() const override;
		virtual void unbind() const override;

	private:
		OpenGLTexture(unsigned int width, unsigned int height, unsigned char* data);

	private:
		friend Texture;
	};
}