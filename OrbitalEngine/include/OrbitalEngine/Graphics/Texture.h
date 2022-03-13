#pragma once

#include "OrbitalEngine/Utils.h"

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

		static TextureData Load(const std::string& filename);
		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		const std::string& getName() const { return m_name;  }

	protected:
		Texture(const std::string& name, unsigned int width, unsigned int height)
			: m_name(name), m_rendererId(0), m_width(width), m_height(height) { }
		static Texture* Create(
			const std::string& name, unsigned int width, unsigned int height, unsigned char* data);
		static Texture* Create(
			const std::string& name, TextureData texXata);

	protected:
		friend TextureManager;

		std::string m_name;
		unsigned int m_rendererId;
		unsigned int m_width;
		unsigned int m_height;
		unsigned int m_wrap_s;
		unsigned int m_wrap_t;
		unsigned int m_minFilter;
		unsigned int m_maxFilter;
	};
}