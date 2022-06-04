#pragma once

#include "Constants.h"
#include "OrbitalEngine/Graphics/Texture.h"

using namespace Orbital;


class Tools
{
public:
	static void Initialize()
	{
		sInstance = new Tools;
	}

	static void Terminate()
	{
		delete sInstance;
	}

	static void RenderIcon(TextureIconIndex iconIndex);
	static bool RenderIconButton(TextureIconIndex iconIndex);

private:
	Tools();

private:
	static inline Tools* sInstance = nullptr;
	WeakRef<Texture> mTexture;
	float mRatio;
};