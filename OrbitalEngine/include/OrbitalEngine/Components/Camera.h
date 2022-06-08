#pragma once

#include "OrbitalEngine/Utils.h"
#include "OrbitalEngine/Components/Component.h"

namespace Orbital
{
	class Camera: public Component
	{
	public:
		Camera();
		Camera(const Camera& other);

		void UpdateMatrices();

		void Move(const glm::vec3& translation);
		void Rotate(const glm::vec2& rotation);
		void Zoom(float zoomModification);

		const Mat4& GetViewMatrix() const { return mViewMatrix; }
		const Mat4& GetProjectionMatrix() const { return mProjectionMatrix; }
		const Mat4& GetVPMatrix() const { return mVPMatrix; }
		const Vec3& GetPosition() const { return mPosition; }
		const Vec3& GetRotation() const { return mRotation; }
		float GetFov() const { return mFov; }
		const Vec3& GetUp() const { return mUp; }
		const Vec3& GetFront() const { return mFront; }
		bool IsOrthographic() const { return mOrthographic; }
		bool IsMainCamera() const { return mMainCamera; }
		const Vec3& GetRight() const { return mRight; }

		void SetOrthographic(bool value = true) { mOrthographic = value; UpdateMatrices(); }
		void SetFOV(float value) { mFov = value; }
		void SetPerspective() { mOrthographic = false; UpdateMatrices(); }
		void SetAspectRatio(float value) { mAspectRatio = value; UpdateMatrices(); }
		void SetPosition(const Vec3& position) { mPosition = position; UpdateMatrices(); };
		void SetRotation(const Vec3& rotation) { mRotation = rotation; UpdateMatrices(); };
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

namespace YAML
{
	template<>
	struct convert<Orbital::Camera>
	{
		static Node encode(const Orbital::Camera& camera)
		{
			Node node;
			node["Main"] = camera.IsMainCamera();
			node["Orthographic"] = camera.IsOrthographic();
			node["FOV"] = camera.GetFov();
			node["Position"] = camera.GetPosition();
			node["Rotation"] = camera.GetRotation();
			return node;
		}

		static bool decode(const Node& node, Orbital::Camera& camera)
		{
			camera.SetMainCamera(node["Main"].as<bool>());
			camera.SetOrthographic(node["Orthographic"].as<bool>());
			camera.SetFOV(node["FOV"].as<float>());
			camera.SetPosition(node["Position"].as<Orbital::Vec3>());
			camera.SetRotation(node["Rotation"].as<Orbital::Vec3>());
			return true;
		}
	};
}