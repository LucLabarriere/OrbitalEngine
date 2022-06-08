#pragma once
#define SCENE_H

#include "OrbitalEngine/Utils.h"
#include "OrbitalEngine/Components/Tag.h"
#include "OrbitalEngine/Components/UUID.h"
#include "OrbitalEngine/Logic/ECS.h"

namespace Orbital
{
	class Camera;
	class SceneManager;

	class Scene : public ECS
	{
	public:
		// Initializing
		Scene(const std::string& tag);
		~Scene();
		virtual void Initialize() override;
		Scene Copy();
		Scene Copy(Scene& newScene);

		// Rendering
		void Begin();
		void End();
		void Render();
		void OnUpdate(Time dt);

		// Tools
		void SetAspectRatio(float aspectRatio);
		void Serialize();
		void SetMainCamera(const Entity& camera) { mMainCamera = camera; }
		void SetUpdating(bool value);

		const std::string& GetTag() const { return mTag; }

	private:
		friend SceneManager;

		Entity mMainCamera;
		std::string mTag;
	};
}

#include "_EntityImp.h"
