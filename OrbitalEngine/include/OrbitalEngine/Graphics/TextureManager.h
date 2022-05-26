#pragma once

#include "OrbitalEngine/Utils.h"
#include "OrbitalEngine/Graphics/Texture.h"

namespace Orbital
{
	class TextureManager : public AssetManager<Texture>
	{
	public:
		static void Initialize() { s_instance = new TextureManager(); }
		static void Terminate() { delete s_instance; }

		bool load(const std::string& tag, const std::string& filepath,
			unsigned int internalFormat = OE_RGB8, unsigned int format = OE_RGB);

		static void Bind(const std::string& tag)
		{
			Get(tag).lock()->bind();
		}

	private:
		TextureManager() : AssetManager<Texture>("TextureManager")
		{
			load("Blank", Settings::GetAssetPath("textures/blank.png"));
			load("Damier", Settings::GetAssetPath("textures/damier.jpeg"));
			load("Icons", Settings::GetAssetPath("textures/icons.png"), OE_RGBA8, OE_RGBA);
		}
	};
}