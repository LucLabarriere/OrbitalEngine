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

		virtual void setWrapS(unsigned int value) = 0;
		virtual void setWrapT(unsigned int value) = 0;
		virtual void setMinFilter(unsigned int value) = 0;
		virtual void setMagFilter(unsigned int value) = 0;

		unsigned int getRendererId() const { return m_rendererId; }
		unsigned int getWidth() const { return m_width; }
		unsigned int getHeight() const { return m_height; }
		unsigned int getWrapS() const { return m_wrapS; }
		unsigned int getWrapT() const { return m_wrapT; }
		unsigned int getMinFilter() const { return m_minFilter; }
		unsigned int getMagFilter() const { return m_magFilter; }

	protected:
		Texture(const std::string& tag, unsigned int width, unsigned int height)
			: Asset(s_id,  tag), m_rendererId(0), m_width(width), m_height(height)
			, m_wrapS(0), m_wrapT(0), m_minFilter(0), m_magFilter(0)
		{
			s_id += 1;
		}
		static Texture* Create(
			const std::string& tag, unsigned int width, unsigned int height, unsigned char* data);
		static Texture* Create(
			const std::string& tag, TextureData texXata);

	protected:
		friend TextureManager;

		unsigned int m_rendererId;
		unsigned int m_width;
		unsigned int m_height;
		unsigned int m_wrapS;
		unsigned int m_wrapT;
		unsigned int m_minFilter;
		unsigned int m_magFilter;

		static inline size_t s_id = 0;
	};
}