#include "OrbitalEngine/Utils/Time.h"
#include "OrbitalEngine/Graphics/CameraController.h"

namespace OrbitalEngine
{
	void CameraController::onUpdate(Time dt)
	{
		if (Inputs::IsKeyPressed(OE_KEY_A))
		{
			m_camera->move(m_translationSpeed * dt.seconds() * glm::vec3(-1.0f, 0.0f, 0.0f));
		}
		if (Inputs::IsKeyPressed(OE_KEY_D))
		{
			m_camera->move(m_translationSpeed * dt.seconds() * glm::vec3(1.0f, 0.0f, 0.0f));
		}
		if (Inputs::IsKeyPressed(OE_KEY_W))
		{
			m_camera->move(m_translationSpeed * dt.seconds() * glm::vec3(0.0f, -1.0f, 0.0f));
		}
		if (Inputs::IsKeyPressed(OE_KEY_S))
		{
			m_camera->move(m_translationSpeed * dt.seconds() * glm::vec3(0.0f, 1.0f, 0.0f));
		}
	}

	void CameraController::onMouseScrolled(const MouseScrolledEvent& e)
	{
		/*Logger::Trace("{}, {}", m_zoomSpeed, e.getYOffset());
		m_camera->zoom(m_zoomSpeed * e.getYOffset());*/
	}
}