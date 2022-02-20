#pragma once

#include "OrbitalEngine/Graphics/Texture.h"

namespace OrbitalEngine
{
	class TextureManager
	{
	public:
		static inline void Initialize()
		{
			if (s_instance == nullptr)
			{
				s_instance = new TextureManager();
				s_instance->load("C:/Users/lucla/Work/Programmes/Orbital/OrbitalEngine/assets/textures/damier.jpeg");
			}
			else
				OE_RAISE_SIGSEGV("TextureManager: You're trying to initialize it again");
		}

		static inline void Terminate() { delete s_instance; }
		static TextureManager* Get() { return s_instance; }

		bool load(const std::string filepath)
		{
			TextureData texData = Texture::Load(filepath);
			if (texData.data == nullptr)
				return false;

			Ref<Texture> texture(Texture::Create(texData));

			m_textures.push_back(texture);
			stbi_image_free(texData.data);

			return true;
		}

	private:
		TextureManager() { }

	private:
		static inline TextureManager* s_instance;
		std::vector<Ref<Texture>> m_textures;
	};
}