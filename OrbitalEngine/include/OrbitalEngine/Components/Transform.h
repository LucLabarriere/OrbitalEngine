#pragma once

#include "OrbitalEngine/Utils.h"

namespace Orbital
{
	namespace Components
	{
		class Transform
		{
		public:
			Transform() { }
			Transform(const Vec3& position) : m_position(position) { }
			Transform(const Vec3& position, const Vec3& rotation) : m_position(position), m_rotation(rotation) { }
			Transform(const Vec3& position, const Vec3& rotation, const Vec3& scale) : m_position(position), m_rotation(rotation), m_scale(scale) { }

			Vec3& Position() { return m_position; }
			Vec3& Rotation() { return m_rotation; }
			Vec3& Scale() { return m_scale; }

			const Vec3& Position() const { return m_position; }
			const Vec3& Rotation() const { return m_rotation; }
			const Vec3& Scale() const { return m_scale; }

		private:
			Vec3 m_position = { 0.0f, 0.0f, 0.0f};
			Vec3 m_rotation = { 0.0f, 0.0f, 0.0f};
			Vec3 m_scale = { 1.0f, 1.0f, 1.0f};
		};
	}
}
