#pragma once

#include "OrbitalEngine/Utils.h"
#include "OrbitalEngine/Events.h"

namespace Orbital
{
	class Window
	{
	public:
		Window(unsigned int width, unsigned int height, const std::string& title)
			: mWidth(width), mHeight(height), mTitle(title) { }
		virtual ~Window() {};

		virtual bool ShouldClose() = 0;
		virtual void OnUpdate() = 0;
		virtual void Shutdown() = 0;
		virtual void EnableCursor() = 0;
		virtual void DisableCursor() = 0;
		void ApplicationCallback(Event& e) { mEventCallback(e); }

		unsigned int GetWidth() { return mWidth; }
		unsigned int GetHeight() { return mHeight; }
		virtual void* GetNativeWindow() const = 0;
		bool IsVSyncEnabled() { return mVsyncEnabled; }

		virtual void SetVSyncEnabled(bool value) = 0;
		void SetApplicationCallBack(std::function<void(Event& e)> callback) { mEventCallback = callback; };

		static Window* Create(unsigned int width, unsigned int height, const std::string& title);

	protected:
		bool mInitialized = false;
		unsigned int mWidth;
		unsigned int mHeight;
		std::string mTitle;
		std::function<void(Event& e)> mEventCallback;
		bool mVsyncEnabled = false;
	};
}