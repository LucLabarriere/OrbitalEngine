#pragma once

#include "Constants.h"
#include "OrbitalEngine/Graphics/Texture.h"

using namespace Orbital;


class Tools
{
public:
	static void Initialize()
	{
		s_instance = new Tools;
	}

	static void Terminate()
	{
		delete s_instance;
	}

	static void RenderIcon(TextureIconIndex iconIndex);
	static bool RenderIconButton(TextureIconIndex iconIndex);

private:
	Tools();

private:
	static inline Tools* s_instance = nullptr;
	WeakRef<Texture> m_texture;
	float m_ratio;
};