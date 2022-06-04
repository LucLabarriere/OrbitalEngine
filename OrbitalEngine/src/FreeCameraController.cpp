#include "OrbitalEngine/Components.h"

namespace Orbital
{
	FreeCameraController::FreeCameraController(const Entity& e)
		: ScriptableEntity(e)
	{
		// TODO: remove all the setting here
		// Check how and when the Constructor, OnLoad and OnStart methods should be called
		// Move the position to a transform component and use it instead
		mCamera = &GetComponent<Camera>();
	}

	void FreeCameraController::onLoad()
	{
		mCamera = &GetComponent<Camera>();
	}

	void FreeCameraController::onStart()
	{
		mCamera = &GetComponent<Camera>();
	}

	void FreeCameraController::onUpdate(Time dt)
	{
		const Vec2 mousePosition = Inputs::GetMousePosition();

		Vec3 direction(0.0f, 0.0f, 0.0f);

		if (Inputs::IsKeyDown(OE_KEY_A))
		{
			direction += mTranslationSpeed * dt.seconds() * Vec3(-1.0f, 0.0f, 0.0f);
		}
		if (Inputs::IsKeyDown(OE_KEY_D))
		{
			direction += mTranslationSpeed * dt.seconds() * Vec3(1.0f, 0.0f, 0.0f);
		}
		if (Inputs::IsKeyDown(OE_KEY_W))
		{
			direction += mTranslationSpeed * dt.seconds() * Vec3(0.0f, 0.0f, 1.0f);
		}
		if (Inputs::IsKeyDown(OE_KEY_S))
		{
			direction += mTranslationSpeed * dt.seconds() * Vec3(0.0f, 0.0f, -1.0f);
		}
		if (Inputs::IsKeyDown(OE_KEY_E))
		{
			direction += mTranslationSpeed * dt.seconds() * Vec3(0.0f, 1.0f, 0.0f);
		}
		if (Inputs::IsKeyDown(OE_KEY_Q))
		{
			direction += mTranslationSpeed * dt.seconds() * Vec3(0.0f, -1.0f, 0.0f);
		}

		mCamera->move(direction);

		if (Inputs::IsMouseButtonDown(OE_MOUSE_BUTTON_2))
		{
			float deltaX = mFormerMousePosition.x - mousePosition.x;
			float deltaY = mFormerMousePosition.y - mousePosition.y;

			Vec2 rotation(deltaY, -deltaX);
			rotation *= mRotationSpeed * dt.seconds();

			mCamera->rotate(rotation);
		}

		mFormerMousePosition.x = mousePosition.x;
		mFormerMousePosition.y = mousePosition.y;
	}

	bool FreeCameraController::onKeyPressed(const KeyPressedEvent& e)
	{
		if (e.getKeyCode() == OE_KEY_KP_0)
		{
			if (mCamera->isOrthographic())
				mCamera->setPerspective();
			else
				mCamera->setOrthographic();
		}
		return false;
	}

	bool FreeCameraController::onMouseScrolled(const MouseScrolledEvent& e)
	{
		mCamera->zoom(mZoomSpeed * e.getYOffset());
		return false;
	}

	void FreeCameraController::setPosition(const Vec3& position)
	{
		mCamera->setPosition(position);
	}

	void FreeCameraController::rotate(const Vec2& rotation)
	{
		mCamera->rotate(rotation);
	}

	float& FreeCameraController::getRotationSpeed() { return mRotationSpeed; }
	float& FreeCameraController::getTranslationSpeed() { return mTranslationSpeed; }
}