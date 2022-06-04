#pragma once
#define SCENE_H

#include "OrbitalEngine/Utils.h"
#include "OrbitalEngine/Components/Tag.h"
#include "OrbitalEngine/Components/UUID.h"
#include "OrbitalEngine/Logic/ECS.h"

namespace Orbital
{
	class Camera;

	class Scene : public ECS
	{
	public:
		// Initializing
		Scene();
		virtual void Initialize() override;
		Scene Copy(Scene& newScene);

		void SetMainCamera(const Entity& camera) { mMainCamera = camera; }
		void SetUpdating(bool value);

		// Rendering
		void Begin();
		void End();
		void Render();
		void OnStart();
		void OnLoad();
		void OnExit();
		void OnUpdate(Time dt);

		// Tools
		void SetAspectRatio(float aspectRatio);
		void Serialize();

	private:
			Entity mMainCamera;
	};
}

#include "_EntityImp.h"
