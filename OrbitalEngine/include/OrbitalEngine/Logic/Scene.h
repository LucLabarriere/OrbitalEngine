#pragma once

#include "OrbitalEngine/Graphics/Camera.h"

namespace OrbitalEngine
{
	class Scene
	{
	public:
		Scene();

	private:
		Ref<Camera> m_camera;
	};
}