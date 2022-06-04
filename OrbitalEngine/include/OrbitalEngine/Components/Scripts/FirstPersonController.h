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

		virtual void onLoad() override;
		virtual void onStart() override;
		virtual void onUpdate(Time dt) override;
		virtual void onExit() override;
		virtual bool onMouseScrolled(const MouseScrolledEvent& e) override;
		void setPosition(const Vec3& position);
		void rotate(const Vec2& rotation);

		float& getRotationSpeed();
		float& getTranslationSpeed();

	private:
		Camera* mCamera = nullptr;
		float mTranslationSpeed = 1.0f;
		float mRotationSpeed = 10.0f;
		float mZoomSpeed = 0.1f;
		Vec2 mFormerMousePosition = { 0.0f, 0.0f };
	};
}