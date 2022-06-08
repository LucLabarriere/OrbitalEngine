#pragma once

#include "OrbitalEngine/Utils/Time.h"
#include "OrbitalEngine/Utils/Misc.h"
#include "OrbitalEngine/Events.h"

namespace Orbital
{
	template <class T> struct ScriptInfo;
}

#define OE_SCRIPT_INFO(scriptName)\
namespace Orbital\
{\
	template <>\
	struct ScriptInfo<scriptName>\
	{ static const char* GetName() { return #scriptName; } };\
}

namespace Orbital
{
	class NativeScript;
	class Entity;

	class NativeScriptManager
	{
	public:
		NativeScriptManager();

		void OnLoad();
		void OnStart();
		void OnUpdate(Time dt);
		void OnExit();
		bool OnKeyPressed(const KeyPressedEvent& e);
		bool OnKeyReleased(const KeyReleasedEvent& e);
		bool OnMouseMoved(const MouseMovedEvent& e);
		bool OnMouseScrolled(const MouseScrolledEvent& e);
		bool OnMouseButtonPressed(const MouseButtonPressedEvent& e);
		bool OnMouseButtonReleased(const MouseButtonReleasedEvent& e);
		bool OnWindowResized(const WindowResizedEvent& e);

		template <typename T, typename ...Args>
		Ref<T> Get();
		template <typename T, typename ...Args>
		Ref<T> Push(const Entity& e, Args... args);

	private:
		std::unordered_map<std::string, Ref<NativeScript>> mScripts;
	};
}