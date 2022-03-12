#pragma once

#include "OrbitalEngine/Graphics/Texture.h"

namespace OrbitalEngine
{
	class TextureManager
	{
	public:
		inline static void Initialize()
		{
			if (s_instance == nullptr)
			{
				s_instance = new TextureManager();
			}
			else
				OE_RAISE_SIGSEGV("TextureManager: You're trying to initialize it again");
		}

		inline static void Terminate() { delete s_instance; }
		static TextureManager* Get() { return s_instance; }

		bool load(const std::string& name, const std::string filepath)
		{
			TextureData texData = Texture::Load(filepath);
			if (texData.data == nullptr)
				return false;

			Ref<Texture> texture(Texture::Create(name, texData));

			m_textures.push_back(texture);
			stbi_image_free(texData.data);

			return true;
		}

		static void Bind(const std::string& tag)
		{
			for (const auto& texture : s_instance->m_textures)
			{
				if (texture->getName() == tag)
				{
					texture->bind();
					return;
				}
			}

			OE_RAISE_SIGSEGV("TextureManager: {} doesn't exists", tag);
		}

	private:
		TextureManager()
		{
			load("Blank", Settings::GetAssetPath("textures/blank.png"));
			load("Damier", Settings::GetAssetPath("textures/damier.jpeg"));
		}

	private:
		inline static TextureManager* s_instance;
		std::vector<Ref<Texture>> m_textures;
	};
}