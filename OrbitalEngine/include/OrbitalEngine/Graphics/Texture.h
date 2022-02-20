#pragma once

#include "OrbitalEngine/Utils.h"
#include "vendor/stb_image.h"

namespace OrbitalEngine
{
	class TextureManager;

	struct TextureData
	{
		int width = 0;
		int height = 0;
		int nChannels = 0;
		unsigned char* data = nullptr;
	};

	class Texture
	{
	public:
		virtual ~Texture() {};

		static TextureData Load(const std::string& filename)
		{
			TextureData data;
			OE_ASSERT(fileExists(filename), "Texture: '{}' does not exist.", filename);
			data.data = stbi_load(
				filename.c_str(), &data.width, &data.height, &data.nChannels, 0);

			return data;
		}

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

	protected:
		Texture(unsigned int width, unsigned int height)
			: m_rendererId(0), m_width(width), m_height(height) { }
		static Texture* Create(unsigned int width, unsigned int height, unsigned char* data);
		static Texture* Create(TextureData texXata);

	protected:
		friend TextureManager;

		unsigned int m_rendererId;
		unsigned int m_width;
		unsigned int m_height;
		unsigned int m_wrap_s;
		unsigned int m_wrap_t;
		unsigned int m_minFilter;
		unsigned int m_maxFilter;
	};
}