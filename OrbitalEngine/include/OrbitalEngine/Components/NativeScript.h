#pragma once

namespace Orbital
{
	template<class T>
	class NativeScript
	{
	public:
		NativeScript<T>(Ref<T>& scriptableEntity) : m_instance(scriptableEntity) { }
		Ref<T> getInstance() { return m_instance; }

	private:
		Ref<T> m_instance;
	};
}