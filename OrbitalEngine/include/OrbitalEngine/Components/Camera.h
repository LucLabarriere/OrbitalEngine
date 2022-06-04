#pragma once

#include "OrbitalEngine/Utils.h"

namespace Orbital
{
	class Camera
	{
	public:
		Camera();

		void updateMatrices();

		void move(const glm::vec3& translation);
		void rotate(const glm::vec2& rotation);
		void zoom(float zoomModification);

		const Mat4& getViewMatrix() const { return m_viewMatrix; }
		const Mat4& getProjectionMatrix() const { return m_projectionMatrix; }
		const Mat4& getVPMatrix() const { return m_VPMatrix; }
		const Vec3& getPosition() const { return m_position; }
		const Vec3& getRight() const { return m_right; }
		const Vec3& getUp() const { return m_up; }
		const Vec3& getFront() const { return m_front; }
		bool isOrthographic() const { return m_orthographic; }
		bool isMainCamera() const { return m_mainCamera; }

		void setOrthographic() { m_orthographic = true; updateMatrices(); }
		void setPerspective() { m_orthographic = false; updateMatrices(); }
		void setAspectRatio(float value) { m_aspectRatio = value; updateMatrices(); }
		void setPosition(const Vec3& position) { m_position = position; updateMatrices(); };
		void setMainCamera(bool value) { m_mainCamera = value; }
		
	private:
		bool m_orthographic = false;
		bool m_mainCamera = true;
		Vec3 m_position;
		Vec3 m_up;
		Vec3 m_front;
		Vec3 m_right;
		Vec3 m_rotation;
		float m_aspectRatio;
		float m_fov;
		float m_zoomLevel = 1.0f;

		Mat4 m_projectionMatrix;
		Mat4 m_viewMatrix;
		Mat4 m_VPMatrix;
	};
}