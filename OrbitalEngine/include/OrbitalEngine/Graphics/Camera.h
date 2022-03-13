#pragma once

#include "OrbitalEngine/Utils.h"

namespace OrbitalEngine
{
	class Camera
	{
	public:
		Camera();

		void updateMatrices();
		const glm::mat4& getViewMatrix() { return m_viewMatrix;  }
		const glm::mat4& getProjectionMatrix() { return m_projectionMatrix; }
		const glm::mat4& getVPMatrix() { return m_VPMatrix; }

		void move(const glm::vec3& translation);
		void rotate(const glm::vec2& rotation);
		void zoom(float zoomModification);

		bool isOrthographic() { return m_orthographic; }
		void setOrthographic() { m_orthographic = true; updateMatrices(); }
		void setPerspective() { m_orthographic = false; updateMatrices(); }
		void setAspectRatio(float value) { m_aspectRatio = value; updateMatrices(); }

	private:
		bool m_orthographic = false;
		glm::vec3 m_position;
		glm::vec3 m_up;
		glm::vec3 m_front;
		glm::vec3 m_right;
		glm::vec3 m_rotation;
		float m_aspectRatio;
		float m_fov;
		float m_zoomLevel = 1.0f;

		glm::mat4 m_projectionMatrix;
		glm::mat4 m_viewMatrix;
		glm::mat4 m_VPMatrix;
	};
}