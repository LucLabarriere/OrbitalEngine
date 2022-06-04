#pragma once

namespace Orbital
{
	template <typename T>
	bool Entity::HasComponent() const
	{
		return (*sActiveScene)->HasComponent<T>(mHandle, mLayerId);
	}

	template <typename T>
	T& Entity::GetComponent() const
	{
		return (*sActiveScene)->GetComponent<T>(mHandle, mLayerId);
	}

	template <typename T>
	T* Entity::TryGetComponent() const
	{
		return (*sActiveScene)->TryGetComponent<T>(mHandle, mLayerId);
	}

	template <typename T>
	void Entity::RemoveComponent() const
	{
		return (*sActiveScene)->RemoveComponent<T>(mHandle, mLayerId);
	}

	template <typename T, typename... Args>
	T& Entity::AddComponent(Args... args)
	{
		return (*sActiveScene)->AddComponent<T>(mHandle, mLayerId, args...);
	}
}