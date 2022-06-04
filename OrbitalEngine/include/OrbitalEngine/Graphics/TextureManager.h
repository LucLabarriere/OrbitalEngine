#pragma once

#include "OrbitalEngine/Utils.h"
#include "OrbitalEngine/Graphics/Texture.h"

namespace Orbital
{
	class TextureManager : public AssetManager<Texture>
	{
	public:
		static void Initialize() { sInstance = new TextureManager(); }
		static void Terminate() { delete sInstance; }

		bool Load(const std::string& tag, const std::string& filepath,
			unsigned int internalFormat = OE_RGB8, unsigned int format = OE_RGB);

		static void Bind(const std::string& tag)
		{
			Get(tag).lock()->Bind();
		}

	private:
		TextureManager() : AssetManager<Texture>("TextureManager")
		{
			Load("Blank", Settings::GetAssetPath("textures/blank.png"));
			Load("Damier", Settings::GetAssetPath("textures/damier.jpeg"));
			Load("Icons", Settings::GetAssetPath("textures/icons.png"), OE_RGBA8, OE_RGBA);
		}
	};
}