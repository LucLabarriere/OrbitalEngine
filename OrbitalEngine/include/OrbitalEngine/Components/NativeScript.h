#pragma once

namespace Orbital
{
	template<class T>
	class NativeScript
	{
	public:
		NativeScript<T>(Ref<T>& scriptableEntity) : mInstance(scriptableEntity) { }
		Ref<T> GetInstance() { return mInstance; }

	private:
		Ref<T> mInstance;
	};
}