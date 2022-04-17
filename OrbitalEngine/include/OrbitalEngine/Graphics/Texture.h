#pragma once

#include "OrbitalEngine/Utils.h"

namespace Orbital
{
	class TextureManager;

	struct TextureData
	{
		int width = 0;
		int height = 0;
		int nChannels = 0;
		unsigned int internalFormat = OE_RGB8;
		unsigned int format = OE_RGB;
		unsigned char* data = nullptr;
	};

	class Texture : public Asset
	{
	public:
		virtual ~Texture() {};

		static TextureData Load(const std::string& filename);
		virtual void bind() const = 0;
		virtual void bind(unsigned int slot) const = 0;
		virtual void unbind() const = 0;

		unsigned int getRendererId() const { return m_rendererId; }
		unsigned int getWidth() const { return m_width; }
		unsigned int getHeight() const { return m_height; }

	protected:
		Texture(const std::string& tag, unsigned int width, unsigned int height)
			: Asset(tag), m_rendererId(0), m_width(width), m_height(height)
		{

		}
		static Texture* Create(
			const std::string& tag, unsigned int width, unsigned int height, unsigned char* data);
		static Texture* Create(
			const std::string& tag, TextureData texXata);

	protected:
		friend TextureManager;

		std::string m_tag;
		unsigned int m_rendererId;
		unsigned int m_width;
		unsigned int m_height;
		unsigned int m_wrap_s;
		unsigned int m_wrap_t;
		unsigned int m_minFilter;
		unsigned int m_maxFilter;
	};
}