#pragma once

#include "OrbitalEngine/Utils.h"
#include "OrbitalEngine/Graphics/Camera.h"
#include "OrbitalEngine/Events.h"

namespace OrbitalEngine
{
	class CameraController
	{
	public:
		CameraController(Ref<Camera>& camera) : m_camera(camera) { }
		void onUpdate(Time dt);
		void onMouseScrolled(const MouseScrolledEvent& e);

	private:
		float m_translationSpeed = 0.2f;
		float m_zoomSpeed = 0.5f;
		Ref<Camera>& m_camera;
	};
}