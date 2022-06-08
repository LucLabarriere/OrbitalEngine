#pragma once

#include "OrbitalEngine/Events.h"
#include "OrbitalEngine/Utils.h"
#include "OrbitalEngine/Logic/NativeScript.h"

namespace Orbital
{
	class Camera;

	class FirstPersonController : public NativeScript
	{
	public:
		FirstPersonController(const Entity& e);

		virtual void OnLoad() override;
		virtual void OnStart() override;
		virtual void OnUpdate(Time dt) override;
		virtual void OnExit() override;
		virtual bool OnMouseScrolled(const MouseScrolledEvent& e) override;

		void Rotate(const Vec2& rotation);
		void SetPosition(const Vec3& position);
		void SetTranslationSpeed(float speed);
		void SetRotationSpeed(float speed);
		void SetZoomSpeed(float speed);

		float& GetTranslationSpeed();
		float& GetRotationSpeed();
		float& GetZoomSpeed();

		float GetTranslationSpeed() const;
		float GetRotationSpeed() const;
		float GetZoomSpeed() const;

	private:
		Camera* mCamera = nullptr;
		float mTranslationSpeed = 1.0f;
		float mRotationSpeed = 10.0f;
		float mZoomSpeed = 0.1f;
		Vec2 mFormerMousePosition = { 0.0f, 0.0f };
	};
}

namespace YAML
{
	template<>
	struct convert<Orbital::FirstPersonController>
	{
		static Node encode(const Orbital::FirstPersonController& fpc)
		{
			Node node;
			node["TranslationSpeed"] = fpc.GetTranslationSpeed();
			node["RotationSpeed"] = fpc.GetRotationSpeed();
			node["ZoomSpeed"] = fpc.GetZoomSpeed();
			return node;
		}
	};
}