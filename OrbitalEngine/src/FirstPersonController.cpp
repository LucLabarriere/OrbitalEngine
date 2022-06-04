#include "OrbitalEngine/Components.h"

namespace Orbital
{
	FirstPersonController::FirstPersonController(const Entity& e)
		: ScriptableEntity(e)
	{
		mCamera = &GetComponent<Camera>();
	}

	void FirstPersonController::onLoad()
	{
		mCamera = &GetComponent<Camera>();
	}

	void FirstPersonController::onStart()
	{
		mCamera = &GetComponent<Camera>();
		Inputs::LockCursor(true);
		
	}

	void FirstPersonController::onUpdate(Time dt)
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

		auto position = mCamera->getPosition();
		position += direction.x * mCamera->getRight() * Vec3(1.0f, 0.0f, 1.0f);
		position += direction.z * mCamera->getFront() * Vec3(1.0f, 0.0f, 1.0f);
		mCamera->setPosition(position);

		float deltaX = mFormerMousePosition.x - mousePosition.x;
		float deltaY = mFormerMousePosition.y - mousePosition.y;

		Vec2 rotation(deltaY, -deltaX);
		rotation *= mRotationSpeed * dt.seconds();

		mCamera->rotate(rotation);

		mFormerMousePosition.x = mousePosition.x;
		mFormerMousePosition.y = mousePosition.y;
	}

	void FirstPersonController::onExit()
	{
		Inputs::LockCursor(false);
	}

	bool FirstPersonController::onMouseScrolled(const MouseScrolledEvent& e)
	{
		mCamera->zoom(mZoomSpeed * e.getYOffset());
		return false;
	}

	void FirstPersonController::setPosition(const Vec3& position)
	{
		mCamera->setPosition(position);
	}

	void FirstPersonController::rotate(const Vec2& rotation)
	{
		mCamera->rotate(rotation);
	}

	float& FirstPersonController::getRotationSpeed() { return mRotationSpeed; }
	float& FirstPersonController::getTranslationSpeed() { return mTranslationSpeed; }
}