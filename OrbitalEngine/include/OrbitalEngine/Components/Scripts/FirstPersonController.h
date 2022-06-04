#pragma once

#include "OrbitalEngine/Events.h"
#include "OrbitalEngine/Utils.h"
#include "OrbitalEngine/Logic/ScriptableEntity.h"

namespace Orbital
{
	class Camera;

	class FirstPersonController : public ScriptableEntity
	{
	public:
		FirstPersonController(const Entity& e);

		virtual void OnLoad() override;
		virtual void OnStart() override;
		virtual void OnUpdate(Time dt) override;
		virtual void onExit() override;
		virtual bool OnMouseScrolled(const MouseScrolledEvent& e) override;
		void SetPosition(const Vec3& position);
		void Rotate(const Vec2& rotation);

		float& GetRotationSpeed();
		float& GetTranslationSpeed();

	private:
		Camera* mCamera = nullptr;
		float mTranslationSpeed = 1.0f;
		float mRotationSpeed = 10.0f;
		float mZoomSpeed = 0.1f;
		Vec2 mFormerMousePosition = { 0.0f, 0.0f };
	};
}