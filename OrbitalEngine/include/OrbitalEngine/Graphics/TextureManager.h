#pragma once

#include "OrbitalEngine/Graphics/Texture.h"

namespace Orbital
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
		static TextureManager* GetInstance() { return s_instance; }
		static Texture& Get(const std::string& textureName)
		{
			for (const auto& texture : s_instance->m_textures)
			{
				if (texture->getName() == textureName)
				{
					return *texture;
				}
			}

			OE_RAISE_SIGSEGV("TextureManager: {} doesn't exists", textureName);
		}

		bool load(const std::string& name, const std::string& filepath,
			unsigned int internalFormat = OE_RGB8, unsigned int format = OE_RGB);

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

		std::vector<Ref<Texture>>::iterator begin() { return m_textures.begin(); }
		std::vector<Ref<Texture>>::iterator end() { return m_textures.end(); }

	private:
		TextureManager()
		{
			load("Blank", Settings::GetAssetPath("textures/blank.png"));
			load("Damier", Settings::GetAssetPath("textures/damier.jpeg"));
			load("Icons", Settings::GetAssetPath("textures/icons.png"), OE_RGBA8, OE_RGBA);
		}



	private:
		inline static TextureManager* s_instance;
		std::vector<Ref<Texture>> m_textures;
	};
}