#pragma once

#include "OrbitalEngine/Components/UUID.h"
#include "OrbitalEngine/Utils/AssetManager.h"

namespace Orbital
{
	class Entity;
	class ScriptableEntity;

	class NativeScriptManager
	{
	public:
		static void Initialize() { s_instance = new NativeScriptManager; }
		static void Terminate() { delete s_instance; }
		static NativeScriptManager* GetInstance() { return s_instance; }

		static void Register(ScriptableEntity* script);
		static void Delete(const UUID& uuid);
		static void DuplicateEntity(const Entity& src, const Entity& dest);

		static void OnLoad();
		static void OnStart();
		static void OnUpdate(Time t);

		std::unordered_map<UUID, ScriptableEntity*>::iterator begin() { return s_scripts.begin(); }
		std::unordered_map<UUID, ScriptableEntity*>::iterator end() { return s_scripts.end(); }

	private:
		static inline std::unordered_map<UUID, ScriptableEntity*> s_scripts;
		static inline NativeScriptManager* s_instance = nullptr;
	};
}