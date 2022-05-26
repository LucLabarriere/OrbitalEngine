#pragma once

#include "OrbitalEngine/Components/NativeScript.h"
#include "OrbitalEngine/Utils/AssetManager.h"

namespace Orbital
{
	class NativeScriptManager
	{
	public:
		static void Initialize() { s_instance = new NativeScriptManager; }
		static void Terminate() { delete s_instance; }

		template <typename T>
		static Ref<T> Create(Entity& e)
		{
			auto newScript = Components::NativeScript<T>(e);
			s_scripts.push_back(newScript.getInstance());

			return newScript.getInstance();
		}

		static void OnLoad()
		{
			for (auto& script : s_scripts)
				script->onLoad();
		}

		static void OnStart()
		{
			for (auto& script : s_scripts)
				script->onStart();
		}

		static void OnUpdate(Time t)
		{
			for (auto& script : s_scripts)
				script->onUpdate(t);
		}

	private:
		static inline std::vector<Ref<Scriptable>> s_scripts;
		static inline NativeScriptManager* s_instance = nullptr;
	};
}