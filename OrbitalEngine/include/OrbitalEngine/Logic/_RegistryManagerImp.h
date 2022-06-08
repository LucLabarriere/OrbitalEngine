#pragma once

#include "RegistryManager.h"
#include "OrbitalEngine/Components/NativeScriptManager.h"

namespace Orbital
{
	template <typename T, typename ...Args>
	Ref<T> RegistryManager::AddNativeScript(const Entity& e, Args... args)
	{
		return GetComponent<NativeScriptManager>(e.GetHandle(), e.GetLayerID()).Push<T>(e, args...);
	}

	template <typename T>
	Ref<T> RegistryManager::GetNativeScript(const entt::entity& handle, const LayerID& layerId)
	{
		return GetComponent<NativeScriptManager>(handle, layerId).Get<T>();
	}
}