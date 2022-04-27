#include "OrbitalEngine/Utils/Time.h"
#include "OrbitalEngine/Graphics/CameraController.h"

namespace Orbital
{
	void CameraController::onUpdate(Time dt)
	{
		const glm::vec2 mousePosition = Inputs::GetMousePosition();

		if (Inputs::IsKeyDown(OE_KEY_A))
		{
			m_camera->move(m_translationSpeed * dt.seconds() * glm::vec3(-1.0f, 0.0f, 0.0f));
		}
		if (Inputs::IsKeyDown(OE_KEY_D))
		{
			m_camera->move(m_translationSpeed * dt.seconds() * glm::vec3(1.0f, 0.0f, 0.0f));
		}
		if (Inputs::IsKeyDown(OE_KEY_W))
		{
			m_camera->move(m_translationSpeed * dt.seconds() * glm::vec3(0.0f, 0.0f, 1.0f));
		}
		if (Inputs::IsKeyDown(OE_KEY_S))
		{
			m_camera->move(m_translationSpeed * dt.seconds() * glm::vec3(0.0f, 0.0f, -1.0f));
		}
		if (Inputs::IsKeyDown(OE_KEY_E))
		{
			m_camera->move(m_translationSpeed * dt.seconds() * glm::vec3(0.0f, 1.0f, 0.0f));
		}
		if (Inputs::IsKeyDown(OE_KEY_Q))
		{
			m_camera->move(m_translationSpeed * dt.seconds() * glm::vec3(0.0f, -1.0f, 0.0f));
		}

		if (Inputs::IsMouseButtonDown(OE_MOUSE_BUTTON_2))
		{
			float deltaX = m_formerMousePosition.x - mousePosition.x;
			float deltaY = m_formerMousePosition.y - mousePosition.y;

			glm::vec2 rotation(deltaY, -deltaX);
			rotation *= m_rotationSpeed * dt.seconds();

			m_camera->rotate(rotation);
		}

		m_formerMousePosition.x = mousePosition.x;
		m_formerMousePosition.y = mousePosition.y;
	}

	void CameraController::onKeyPressed(const KeyPressedEvent& e)
	{
		if (e.getKeyCode() == OE_KEY_KP_0)
		{
			if (m_camera->isOrthographic())
				m_camera->setPerspective();
			else
				m_camera->setOrthographic();
		}
	}

	void CameraController::onMouseScrolled(const MouseScrolledEvent& e)
	{
		m_camera->zoom(m_zoomSpeed * e.getYOffset());
	}
}