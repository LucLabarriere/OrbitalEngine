#pragma once

#include "OrbitalEngine/Events.h"

namespace Orbital
{
	class Window;

	class Inputs
	{
	public:
		static void Initialize(Scope<Window>& window);
		static void Terminate() { delete sInstance;  }
		static bool IsKeyDown(int keyCode) { return sInstance->IsKeyDownImpl(keyCode); };
		static bool IsMouseButtonDown(int buttonCode) { return sInstance->IsMouseButtonDownImpl(buttonCode); };
		static void LockCursor(bool value) { sInstance->LockCursorImpl(value); };
		static const Vec2 GetMousePosition() { return sInstance->GetMousePositionImpl(); }
		static bool IsMouseEnabled() { return sInstance->IsMouseEnabledImpl(); }

	protected:
		Inputs() { };

	private:
		virtual bool IsKeyDownImpl(int keyCode) const = 0;
		virtual bool IsMouseButtonDownImpl(int buttonCode) const = 0;
		virtual void LockCursorImpl(bool value) = 0;
		virtual const Vec2 GetMousePositionImpl() const = 0;
		virtual bool IsMouseEnabledImpl() const = 0;

	private:
		inline static Inputs* sInstance = nullptr;
	};
}