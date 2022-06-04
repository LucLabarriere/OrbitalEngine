#pragma once

#include "OrbitalEngine/Utils.h"
#include "OrbitalEngine/Components/Component.h"

namespace Orbital
{
	class Camera: public Component
	{
	public:
		Camera();

		void UpdateMatrices();

		void Move(const glm::vec3& translation);
		void Rotate(const glm::vec2& rotation);
		void Zoom(float zoomModification);

		const Mat4& GetViewMatrix() const { return mViewMatrix; }
		const Mat4& GetProjectionMatrix() const { return mProjectionMatrix; }
		const Mat4& GetVPMatrix() const { return mVPMatrix; }
		const Vec3& GetPosition() const { return mPosition; }
		const Vec3& GetRight() const { return mRight; }
		const Vec3& GetUp() const { return mUp; }
		const Vec3& GetFront() const { return mFront; }
		bool IsOrthographic() const { return mOrthographic; }
		bool IsMainCamera() const { return mMainCamera; }

		void SetOrthographic() { mOrthographic = true; UpdateMatrices(); }
		void SetPerspective() { mOrthographic = false; UpdateMatrices(); }
		void SetAspectRatio(float value) { mAspectRatio = value; UpdateMatrices(); }
		void SetPosition(const Vec3& position) { mPosition = position; UpdateMatrices(); };
		void SetMainCamera(bool value) { mMainCamera = value; }
		
	private:
		bool mOrthographic = false;
		bool mMainCamera = true;
		Vec3 mPosition;
		Vec3 mUp;
		Vec3 mFront;
		Vec3 mRight;
		Vec3 mRotation;
		float mAspectRatio;
		float mFov;
		float mZoomLevel = 1.0f;

		Mat4 mProjectionMatrix;
		Mat4 mViewMatrix;
		Mat4 mVPMatrix;
	};
}