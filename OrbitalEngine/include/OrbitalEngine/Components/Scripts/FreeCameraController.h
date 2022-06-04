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

		virtual void onLoad() override;
		virtual void onStart() override;
		virtual void onUpdate(Time dt) override;
		virtual bool onKeyPressed(const KeyPressedEvent& e) override;
		virtual bool onMouseScrolled(const MouseScrolledEvent& e) override;
		void rotate(const Vec2& rotation);
		void setPosition(const Vec3& position);

		float& getRotationSpeed();
		float& getTranslationSpeed();

	private:
		Camera* mCamera = nullptr;
		float mTranslationSpeed = 10.0f;
		float mRotationSpeed = 35.0f;
		float mZoomSpeed = 0.1f;
		Vec2 mFormerMousePosition = { 0.0f, 0.0f };
	};
}



