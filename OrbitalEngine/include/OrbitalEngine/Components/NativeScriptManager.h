#pragma once

#include "OrbitalEngine/Logic/NativeScript.h"


namespace Orbital
{
	template <class T> struct ScriptInfo;
}

#define OE_SCRIPT_INFO(scriptName)\
namespace Orbital\
{\
	template <>\
	struct ScriptInfo<scriptName>\
	{ static std::string GetName() { return #scriptName; } };\
}

namespace Orbital
{
	class NativeScriptManager
	{
	public:
		NativeScriptManager() { };

		void OnLoad()
			{ for (auto& [ scriptName, script ] : mScripts) script->OnLoad(); }
		void OnStart()
			{ for (auto& [ scriptName, script ] : mScripts) script->OnStart(); }
		void OnUpdate(Time dt)
			{ for (auto& [ scriptName, script ] : mScripts) script->OnUpdate(dt); }
		void OnExit()
			{ for (auto& [ scriptName, script ] : mScripts) script->OnExit(); }
		bool OnKeyPressed(const KeyPressedEvent& e)
			{ for (auto& [ scriptName, script ] : mScripts) script->OnKeyPressed(e); }
		bool OnKeyReleased(const KeyReleasedEvent& e)
			{ for (auto& [ scriptName, script ] : mScripts) script->OnKeyReleased(e); }
		bool OnMouseMoved(const MouseMovedEvent& e)
			{ for (auto& [ scriptName, script ] : mScripts) script->OnMouseMoved(e); }
		bool OnMouseScrolled(const MouseScrolledEvent& e)
			{ for (auto& [ scriptName, script ] : mScripts) script->OnMouseScrolled(e); }
		bool OnMouseButtonPressed(const MouseButtonPressedEvent& e)
			{ for (auto& [ scriptName, script ] : mScripts) script->OnMouseButtonPressed(e); }
		bool OnMouseButtonReleased(const MouseButtonReleasedEvent& e)
			{ for (auto& [ scriptName, script ] : mScripts) script->OnMouseButtonReleased(e); }
		bool OnWindowResized(const WindowResizedEvent& e)
			{ for (auto& [ scriptName, script ] : mScripts) script->OnWindowResized(e); }

		template <typename T, typename ...Args>
		Ref<T>& Get()
		{
			//TODO use this
			Ref<T>& script = mScripts.find(ScriptInfo<T>::GetName())->second;
			return script;
		}

		template <typename T, typename ...Args>
		Ref<T>& Push(Args... args)
		{
			mScripts.emplace(ScriptInfo<T>::GetName(), CreateRef<T>(args...));
		}

	private:
		std::unordered_map<std::string, Ref<NativeScript>> mScripts;
	};
}