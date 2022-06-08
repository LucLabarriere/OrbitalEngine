#include "OrbitalEngine/Components.h"

namespace Orbital
{
	FreeCameraController::FreeCameraController()
		: NativeScript()
	{
		// TODO: remove all the setting here
		// Check how and when the Constructor, OnLoad and OnStart methods should be called
		// Move the position to a transform component and use it instead
		mCamera = &GetComponent<Camera>();
	}

	FreeCameraController::FreeCameraController(const Entity& e)
		: NativeScript(e)
	{
		// TODO: remove all the setting here
		// Check how and when the Constructor, OnLoad and OnStart methods should be called
		// Move the position to a transform component and use it instead
		mCamera = &GetComponent<Camera>();
	}

	FreeCameraController::FreeCameraController(const FreeCameraController& other)
		: NativeScript(Entity(other.GetLayerID(), other.GetHandle()))
		, mTranslationSpeed(other.mTranslationSpeed)
		, mRotationSpeed(other.mRotationSpeed)
		, mZoomSpeed(other.mZoomSpeed)
	{
		mCamera = &GetComponent<Camera>();
	}

	void FreeCameraController::OnLoad()
	{
		mCamera = &GetComponent<Camera>();
	}

	void FreeCameraController::OnStart()
	{
		mCamera = &GetComponent<Camera>();
	}

	void FreeCameraController::OnUpdate(Time dt)
	{
		const Vec2 mousePosition = Inputs::GetMousePosition();

		Vec3 direction(0.0f, 0.0f, 0.0f);

		if (Inputs::IsKeyDown(OE_KEY_A))
		{
			direction += mTranslationSpeed * dt.Seconds() * Vec3(-1.0f, 0.0f, 0.0f);
		}
		if (Inputs::IsKeyDown(OE_KEY_D))
		{
			direction += mTranslationSpeed * dt.Seconds() * Vec3(1.0f, 0.0f, 0.0f);
		}
		if (Inputs::IsKeyDown(OE_KEY_W))
		{
			direction += mTranslationSpeed * dt.Seconds() * Vec3(0.0f, 0.0f, 1.0f);
		}
		if (Inputs::IsKeyDown(OE_KEY_S))
		{
			direction += mTranslationSpeed * dt.Seconds() * Vec3(0.0f, 0.0f, -1.0f);
		}
		if (Inputs::IsKeyDown(OE_KEY_E))
		{
			direction += mTranslationSpeed * dt.Seconds() * Vec3(0.0f, 1.0f, 0.0f);
		}
		if (Inputs::IsKeyDown(OE_KEY_Q))
		{
			direction += mTranslationSpeed * dt.Seconds() * Vec3(0.0f, -1.0f, 0.0f);
		}

		mCamera->Move(direction);

		if (Inputs::IsMouseButtonDown(OE_MOUSE_BUTTON_2))
		{
			float deltaX = mFormerMousePosition.x - mousePosition.x;
			float deltaY = mFormerMousePosition.y - mousePosition.y;

			Vec2 rotation(deltaY, -deltaX);
			rotation *= mRotationSpeed * dt.Seconds();

			mCamera->Rotate(rotation);
		}

		mFormerMousePosition.x = mousePosition.x;
		mFormerMousePosition.y = mousePosition.y;
	}

	bool FreeCameraController::OnKeyPressed(const KeyPressedEvent& e)
	{
		if (e.GetKeyCode() == OE_KEY_KP_0)
		{
			if (mCamera->IsOrthographic())
				mCamera->SetPerspective();
			else
				mCamera->SetOrthographic();
		}
		return false;
	}

	bool FreeCameraController::OnMouseScrolled(const MouseScrolledEvent& e)
	{
		mCamera->Zoom(mZoomSpeed * e.GetYOffset());
		return false;
	}

	void FreeCameraController::SetPosition(const Vec3& position)
	{
		mCamera->SetPosition(position);
	}

	void FreeCameraController::SetTranslationSpeed(float speed)
	{
		mTranslationSpeed = speed;
	}

	void FreeCameraController::SetRotationSpeed(float speed)
	{
		mRotationSpeed = speed;
	}

	void FreeCameraController::SetZoomSpeed(float speed)
	{
		mZoomSpeed = speed;
	}

	void FreeCameraController::Rotate(const Vec2& rotation)
	{
		mCamera->Rotate(rotation);
	}

	float& FreeCameraController::GetRotationSpeed() { return mRotationSpeed; }
	float& FreeCameraController::GetTranslationSpeed() { return mTranslationSpeed; }
	float& FreeCameraController::GetZoomSpeed() { return mZoomSpeed; }
	float FreeCameraController::GetRotationSpeed() const { return mRotationSpeed; }
	float FreeCameraController::GetTranslationSpeed() const { return mTranslationSpeed; }
	float FreeCameraController::GetZoomSpeed() const { return mZoomSpeed; }
}