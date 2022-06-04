#pragma once

#include "OrbitalEngine/Utils.h"
#include "OrbitalEngine/Components/Component.h"

namespace Orbital
{
	class Transform : public Component
	{
	public:
		Transform() { }
		Transform(const Transform& other) : mPosition(other.GetPosition()) , mRotation(other.GetRotation()), mScale(other.GetScale()) { }
		Transform(const Vec3& position) : mPosition(position) { }
		Transform(const Vec3& position, const Vec3& rotation) : mPosition(position), mRotation(rotation) { }
		Transform(const Vec3& position, const Vec3& rotation, const Vec3& scale) : mPosition(position), mRotation(rotation), mScale(scale) { }

		Vec3& GetPosition() { mDirty = true; return mPosition; }
		Vec3& GetRotation() { mDirty = true; return mRotation; }
		Vec3& GetScale() { mDirty = true; return mScale; }

		const Vec3& GetPosition() const { return mPosition; }
		const Vec3& GetRotation() const { return mRotation; }
		const Vec3& GetScale() const { return mScale; }

		bool IsDirty() const { return mDirty; }
		void CleanUp() { mDirty = false; }
		void Dirty() { mDirty = true; }

	private:
		Vec3 mPosition = { 0.0f, 0.0f, 0.0f};
		Vec3 mRotation = { 0.0f, 0.0f, 0.0f};
		Vec3 mScale = { 1.0f, 1.0f, 1.0f};
		bool mDirty = true;
	};
}
