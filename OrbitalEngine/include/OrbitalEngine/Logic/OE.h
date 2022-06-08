#pragma once

namespace Orbital
{
	class SceneManager;
	class Scene;

	class OE
	{
	public:
		static inline Scene* ActiveScene;
		static inline SceneManager* SceneManager;
	};
}