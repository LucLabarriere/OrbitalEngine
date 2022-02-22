#include "OrbitalEngine/Graphics/Camera.h"
#include "OrbitalEngine/Utils.h"

namespace OrbitalEngine
{
	Camera::Camera() : m_position(0.0f, 0.0f, -0.5f), m_up(0.0f, 1.0f, 0.0f), m_front(0.0f, 0.0f, 1.0f)
		, m_right(1.0f, 0.0f, 0.0f), m_rotation(0.0f), m_fov(1.0f)
		, m_viewMatrix(1.0f), m_projectionMatrix(1.0f), m_VPMatrix(1.0f)
	{
		updateMatrices();
	}

	void Camera::updateMatrices()
	{
		m_viewMatrix = glm::lookAt(m_position, m_position + m_front, m_up);
		m_projectionMatrix = glm::ortho(- m_zoomLevel, m_zoomLevel, - m_zoomLevel, m_zoomLevel, -1.0f, 1.0f);
		m_VPMatrix = m_projectionMatrix * m_viewMatrix;
	}

	void Camera::move(const glm::vec3& translation)
	{
		m_position += translation;
		updateMatrices();
	}

	void Camera::zoom(float zoomModification)
	{
		m_zoomLevel += zoomModification;
		updateMatrices();
	}
}