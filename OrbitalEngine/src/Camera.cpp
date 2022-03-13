#include "OrbitalEngine/Graphics/Camera.h"
#include "OrbitalEngine/Utils.h"

namespace OrbitalEngine
{
	Camera::Camera() : m_position(0.0f, 0.0f, -0.5f), m_up(0.0f, 1.0f, 0.0f), m_front(0.0f, 0.0f, 1.0f)
		, m_right(1.0f, 0.0f, 0.0f), m_rotation(0.0f, 90.0f, 0.0f), m_fov(60.0f)
		, m_aspectRatio((float)Settings::Get(Settings::UIntSetting::WindowWidth) / (float)Settings::Get(Settings::UIntSetting::WindowHeight))
		, m_viewMatrix(1.0f), m_projectionMatrix(1.0f), m_VPMatrix(1.0f)
	{
		updateMatrices();
	}

	void Camera::updateMatrices()
	{
		m_front.x = cos(glm::radians(m_rotation.y)) * cos(glm::radians(m_rotation.x));
		m_front.y = sin(glm::radians(m_rotation.x));
		m_front.z = sin(glm::radians(m_rotation.y)) * cos(glm::radians(m_rotation.x));
		m_front = glm::normalize(m_front);
		m_right = glm::normalize(glm::cross(m_front, m_up));

		if (m_orthographic)
		{
			m_projectionMatrix = glm::ortho(
				-m_zoomLevel * m_aspectRatio, m_zoomLevel * m_aspectRatio,
				-m_zoomLevel, m_zoomLevel,
				0.1f, 100.0f);
		}
		else
			m_projectionMatrix = glm::perspective(glm::radians(m_fov), m_aspectRatio, 0.1f, 100.0f);

		m_viewMatrix = glm::lookAt(m_position, m_position + m_front, m_up);
		m_VPMatrix = m_projectionMatrix * m_viewMatrix;
	}

	void Camera::move(const glm::vec3& translation)
	{
		m_position += translation.x * m_right;
		m_position += translation.y * m_up;
		m_position += translation.z * m_front;
		updateMatrices();
	}

	void Camera::rotate(const glm::vec2& rotation)
	{
		m_rotation += glm::vec3(rotation, 0.0f);

		if (m_rotation.x > 89.0f)
			m_rotation.x = 89.0f;
		else if (m_rotation.x < -89.0f)
			m_rotation.x = -89.0f;

		updateMatrices();
	}

	void Camera::zoom(float zoomModification)
	{
		if (m_orthographic)
			m_zoomLevel -= zoomModification;
		else
			move(glm::vec3(0.0f, 0.0f, zoomModification));

		updateMatrices();
	}
}