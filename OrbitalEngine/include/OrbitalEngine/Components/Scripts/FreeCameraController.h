#pragma once

#include "OrbitalEngine/Events.h"
#include "OrbitalEngine/Utils.h"
#include "OrbitalEngine/Logic/ScriptableEntity.h"
#include "OrbitalEngine/Components/Camera.h"

namespace Orbital
{
	class FreeCameraController : public ScriptableEntity
	{
	public:
		FreeCameraController(const Entity& e);

		virtual void OnLoad() override;
		virtual void OnStart() override;
		virtual void OnUpdate(Time dt) override;
		virtual bool OnKeyPressed(const KeyPressedEvent& e) override;
		virtual bool OnMouseScrolled(const MouseScrolledEvent& e) override;
		void Rotate(const Vec2& rotation);
		void SetPosition(const Vec3& position);

		float& GetRotationSpeed();
		float& GetTranslationSpeed();

	private:
		Camera* mCamera = nullptr;
		float mTranslationSpeed = 10.0f;
		float mRotationSpeed = 35.0f;
		float mZoomSpeed = 0.1f;
		Vec2 mFormerMousePosition = { 0.0f, 0.0f };
	};
}



