#pragma once

#include "OrbitalEngine/Events.h"
#include "OrbitalEngine/Utils.h"
#include "OrbitalEngine/Logic/NativeScript.h"
#include "OrbitalEngine/Components/Camera.h"

namespace Orbital
{
	class FreeCameraController : public NativeScript
	{
	public:
		FreeCameraController();
		FreeCameraController(const Entity& e);
		FreeCameraController(const FreeCameraController& other);

		virtual void OnLoad() override;
		virtual void OnStart() override;
		virtual void OnUpdate(Time dt) override;
		virtual bool OnKeyPressed(const KeyPressedEvent& e) override;
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
		float mTranslationSpeed = 10.0f;
		float mRotationSpeed = 35.0f;
		float mZoomSpeed = 0.1f;
		Vec2 mFormerMousePosition = { 0.0f, 0.0f };
	};
}

namespace YAML
{
	template<>
	struct convert<Orbital::FreeCameraController>
	{
		static Node encode(const Orbital::FreeCameraController& fcc)
		{
			Node node;
			node["TranslationSpeed"] = fcc.GetTranslationSpeed();
			node["RotationSpeed"] = fcc.GetRotationSpeed();
			node["ZoomSpeed"] = fcc.GetZoomSpeed();

			return node;
		}

		static bool decode(const Node& node, Orbital::FreeCameraController& fcc)
		{
			fcc.SetTranslationSpeed(node["TranslationSpeed"].as<float>());
			fcc.SetRotationSpeed(node["RotationSpeed"].as<float>());
			fcc.SetZoomSpeed(node["ZoomSpeed"].as<float>());

			return true;
		}
	};
}