#include "OrbitalEngine/Logic/ECS.h"

namespace Orbital
{
	FirstPersonController::FirstPersonController(const Entity& e)
		: NativeScript(e)
	{
		mCamera = &GetComponent<Camera>();
	}

	void FirstPersonController::OnLoad()
	{
		mCamera = &GetComponent<Camera>();
	}

	void FirstPersonController::OnStart()
	{
		mCamera = &GetComponent<Camera>();
		Inputs::LockCursor(true);
		
	}

	void FirstPersonController::OnUpdate(Time dt)
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

		auto position = mCamera->GetPosition();
		position += direction.x * mCamera->GetRight() * Vec3(1.0f, 0.0f, 1.0f);
		position += direction.z * mCamera->GetFront() * Vec3(1.0f, 0.0f, 1.0f);
		mCamera->SetPosition(position);

		float deltaX = mFormerMousePosition.x - mousePosition.x;
		float deltaY = mFormerMousePosition.y - mousePosition.y;

		Vec2 rotation(deltaY, -deltaX);
		rotation *= mRotationSpeed * dt.Seconds();

		mCamera->Rotate(rotation);

		mFormerMousePosition.x = mousePosition.x;
		mFormerMousePosition.y = mousePosition.y;
	}

	void FirstPersonController::OnExit()
	{
		Inputs::LockCursor(false);
	}

	bool FirstPersonController::OnMouseScrolled(const MouseScrolledEvent& e)
	{
		mCamera->Zoom(mZoomSpeed * e.GetYOffset());
		return false;
	}

	void FirstPersonController::Rotate(const Vec2& rotation)
	{
		mCamera->Rotate(rotation);
	}

	void FirstPersonController::SetPosition(const Vec3& position)
	{
		mCamera->SetPosition(position);
	}

	void FirstPersonController::SetTranslationSpeed(float speed)
	{
		mTranslationSpeed = speed;
	}

	void FirstPersonController::SetRotationSpeed(float speed)
	{
		mRotationSpeed = speed;
	}

	void FirstPersonController::SetZoomSpeed(float speed)
	{
		mZoomSpeed = speed;
	}

	float& FirstPersonController::GetRotationSpeed() { return mRotationSpeed; }
	float& FirstPersonController::GetTranslationSpeed() { return mTranslationSpeed; }
	float& FirstPersonController::GetZoomSpeed() { return mZoomSpeed; }

	float FirstPersonController::GetRotationSpeed() const { return mRotationSpeed; }
	float FirstPersonController::GetTranslationSpeed() const { return mTranslationSpeed; }
	float FirstPersonController::GetZoomSpeed() const { return mZoomSpeed; }
}