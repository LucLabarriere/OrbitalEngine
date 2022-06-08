#pragma once

#include "OrbitalEngine/Logic/OE.h"

namespace Orbital
{
	template <typename T>
	bool Entity::HasComponent() const
	{
		return OE::ActiveScene->HasComponent<T>(mHandle, mLayerId);
	}

	template <typename T>
	T& Entity::GetComponent() const
	{
		return OE::ActiveScene->GetComponent<T>(mHandle, mLayerId);
	}

	template <typename T>
	T* Entity::TryGetComponent() const
	{
		return OE::ActiveScene->TryGetComponent<T>(mHandle, mLayerId);
	}

	template <typename T>
	void Entity::RemoveComponent() const
	{
		return OE::ActiveScene->RemoveComponent<T>(mHandle, mLayerId);
	}

	template <typename T, typename... Args>
	T& Entity::AddComponent(Args... args)
	{
		return OE::ActiveScene->AddComponent<T>(mHandle, mLayerId, args...);
	}

	template <typename T, typename ...Args>
	Ref<T> Entity::AddNativeScript(Args... args)
	{
		return OE::ActiveScene->AddNativeScript<T>(*this, args...);
	}

	template <typename T>
	Ref<T> Entity::GetNativeScript()
	{
		return OE::ActiveScene->GetNativeScript<T>(mHandle, mLayerId);
	}
}