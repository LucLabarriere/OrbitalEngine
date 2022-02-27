#pragma once

#include "OrbitalEngine/Utils.h"
#include "OrbitalEngine/Graphics/Camera.h"
#include "OrbitalEngine/Events.h"

namespace OrbitalEngine
{
	class CameraController
	{
	public:
		CameraController(Ref<Camera>& camera)
			: m_camera(camera), m_formerMousePosition(0.0f) { }
		void onUpdate(Time dt);
		void onKeyPressed(const KeyPressedEvent& e);
		void onMouseScrolled(const MouseScrolledEvent& e);

	private:
		float m_translationSpeed = 2.0f;
		float m_rotationSpeed = 10.0f;
		float m_zoomSpeed = 0.1f;
		glm::vec2 m_formerMousePosition;
		Ref<Camera> m_camera;
	};
}