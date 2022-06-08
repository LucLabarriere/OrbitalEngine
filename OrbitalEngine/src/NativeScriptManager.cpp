#include "OrbitalEngine/Components/NativeScriptManager.h"
#include "OrbitalEngine/Logic/NativeScript.h"

namespace Orbital
{
	NativeScriptManager::NativeScriptManager() : mScripts() { };

	void NativeScriptManager::OnLoad()
	{
		for (auto& [scriptName, script] : mScripts) script->OnLoad();
	}
	void NativeScriptManager::OnStart()
	{
		for (auto& [scriptName, script] : mScripts) script->OnStart();
	}
	void NativeScriptManager::OnUpdate(Time dt)
	{
		for (auto& [scriptName, script] : mScripts) script->OnUpdate(dt);
	}
	void NativeScriptManager::OnExit()
	{
		for (auto& [scriptName, script] : mScripts) script->OnExit();
	}
	bool NativeScriptManager::OnKeyPressed(const KeyPressedEvent& e)
	{
		for (auto& [scriptName, script] : mScripts)
		{
			if (script->OnKeyPressed(e))
				return true;
		}
		return false;
	}
	bool NativeScriptManager::OnKeyReleased(const KeyReleasedEvent& e)
	{
		for (auto& [scriptName, script] : mScripts)
		{
			if (script->OnKeyReleased(e))
				return true;
		}
		return false;
	}
	bool NativeScriptManager::OnMouseMoved(const MouseMovedEvent& e)
	{
		for (auto& [scriptName, script] : mScripts)
		{
			if (script->OnMouseMoved(e))
				return true;
		}
		return false;
	}
	bool NativeScriptManager::OnMouseScrolled(const MouseScrolledEvent& e)
	{
		for (auto& [scriptName, script] : mScripts)
		{
			if (script->OnMouseScrolled(e))
				return true;
		}
		return false;
	}
	bool NativeScriptManager::OnMouseButtonPressed(const MouseButtonPressedEvent& e)
	{
		for (auto& [scriptName, script] : mScripts)
		{
			if (script->OnMouseButtonPressed(e))
				return true;
		}
		return false;
	}
	bool NativeScriptManager::OnMouseButtonReleased(const MouseButtonReleasedEvent& e)
	{
		for (auto& [scriptName, script] : mScripts)
		{
			if (script->OnMouseButtonReleased(e))
				return true;
		}
		return false;
	}
	bool NativeScriptManager::OnWindowResized(const WindowResizedEvent& e)
	{
		for (auto& [scriptName, script] : mScripts)
		{
			if (script->OnWindowResized(e))
				return true;
		}
		return false;
	}
}