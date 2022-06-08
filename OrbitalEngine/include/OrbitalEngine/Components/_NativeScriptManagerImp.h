#pragma once

#include "NativeScriptManager.h"
#include "OrbitalEngine/Logic/NativeScript.h"

namespace Orbital
{
	template <typename T, typename ...Args>
	Ref<T> NativeScriptManager::Get()
	{
		auto found = mScripts.find(ScriptInfo<T>::GetName());
		if (found != mScripts.end())
			return dynamic_pointer_cast<T>(found->second);
		OE_RAISE_SIGSEGV("NativeScriptManager: {} was not registered", ScriptInfo<T>::GetName());
	}

	template <typename T, typename ...Args>
	Ref<T> NativeScriptManager::Push(const Entity& e, Args... args)
	{
		mScripts.emplace(ScriptInfo<T>::GetName(), CreateRef<T>(e, args...));
		return Get<T>();
	}
}