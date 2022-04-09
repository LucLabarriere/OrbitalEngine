#pragma once

#include "OrbitalEngine/Utils.h"

namespace Orbital
{
	class Camera
	{
	public:
		Camera();

		void updateMatrices();
		const Mat4& getViewMatrix() { return m_viewMatrix;  }
		const Mat4& getProjectionMatrix() { return m_projectionMatrix; }
		const Mat4& getVPMatrix() { return m_VPMatrix; }
		const Vec3& getPosition() { return m_position; }

		void move(const glm::vec3& translation);
		void rotate(const glm::vec2& rotation);
		void zoom(float zoomModification);

		bool isOrthographic() { return m_orthographic; }
		void setOrthographic() { m_orthographic = true; updateMatrices(); }
		void setPerspective() { m_orthographic = false; updateMatrices(); }
		void setAspectRatio(float value) { m_aspectRatio = value; updateMatrices(); }

	private:
		bool m_orthographic = false;
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