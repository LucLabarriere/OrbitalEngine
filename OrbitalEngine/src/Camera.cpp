#include "OrbitalEngine/Components/Camera.h"
#include "OrbitalEngine/Utils.h"

namespace Orbital
{
	Camera::Camera() : mPosition(0.0f, 0.0f, -0.5f), mUp(0.0f, 1.0f, 0.0f), mFront(0.0f, 0.0f, 1.0f)
		, mRight(1.0f, 0.0f, 0.0f), mRotation(0.0f, 90.0f, 0.0f), mFov(60.0f)
		, mAspectRatio((float)Settings::Get(Settings::UIntSetting::WindowWidth) / (float)Settings::Get(Settings::UIntSetting::WindowHeight))
		, mViewMatrix(1.0f), mProjectionMatrix(1.0f), mVPMatrix(1.0f)
	{
		UpdateMatrices();
	}

	Camera::Camera(const Camera& other)
		: mPosition(other.mPosition), mUp(other.mUp), mFront(other.mFront)
		, mRight(other.mRight), mRotation(other.mRotation), mFov(other.mFov)
		, mAspectRatio((float)Settings::Get(Settings::UIntSetting::WindowWidth) / (float)Settings::Get(Settings::UIntSetting::WindowHeight))
		, mViewMatrix(other.mViewMatrix), mProjectionMatrix(other.mProjectionMatrix), mVPMatrix(other.mVPMatrix)

	{

	}

	void Camera::UpdateMatrices()
	{
		mFront.x = cos(glm::radians(mRotation.y)) * cos(glm::radians(mRotation.x));
		mFront.y = sin(glm::radians(mRotation.x));
		mFront.z = sin(glm::radians(mRotation.y)) * cos(glm::radians(mRotation.x));
		mFront = glm::normalize(mFront);
		mRight = glm::normalize(glm::cross(mFront, mUp));

		if (mOrthographic)
		{
			mProjectionMatrix = glm::ortho(
				-mZoomLevel * mAspectRatio, mZoomLevel * mAspectRatio,
				-mZoomLevel, mZoomLevel,
				0.1f, 100.0f);
		}
		else
			mProjectionMatrix = glm::perspective(glm::radians(mFov), mAspectRatio, 0.1f, 100.0f);

		mViewMatrix = glm::lookAt(mPosition, mPosition + mFront, mUp);
		mVPMatrix = mProjectionMatrix * mViewMatrix;
	}

	void Camera::Move(const glm::vec3& translation)
	{
		mPosition += translation.x * mRight;
		mPosition += translation.y * mUp;
		mPosition += translation.z * mFront;
		UpdateMatrices();
	}

	void Camera::Rotate(const glm::vec2& rotation)
	{
		mRotation += glm::vec3(rotation, 0.0f);

		if (mRotation.x > 89.0f)
			mRotation.x = 89.0f;
		else if (mRotation.x < -89.0f)
			mRotation.x = -89.0f;

		UpdateMatrices();
	}

	void Camera::Zoom(float zoomModification)
	{
		if (mOrthographic)
			mZoomLevel -= zoomModification;
		else
			Move(glm::vec3(0.0f, 0.0f, zoomModification));

		UpdateMatrices();
	}
}