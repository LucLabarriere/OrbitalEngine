#include "OrbitalEngine/Logic/NativeScriptManager.h"
#include "OrbitalEngine/Logic/ScriptableEntity.h"

namespace Orbital
{
	void NativeScriptManager::Register(ScriptableEntity* script)
	{
		s_scripts.emplace(script->GetComponent<UUID>(), script);
	}

	void NativeScriptManager::Delete(const UUID& uuid)
	{
		s_scripts.erase(uuid);
	}

	void NativeScriptManager::DuplicateEntity(const Entity& src, const Entity& dest)
	{
		// TODO
		// loop through scriptableEntities
		// retrieve their type_hash
		// 
	}

	void NativeScriptManager::OnLoad()
	{
		/*for (auto& [uuid, script] : s_scripts)
			script->onLoad();*/
	}

	void NativeScriptManager::OnStart()
	{
		/*for (auto& [uuid, script] : s_scripts)
			script->onStart();*/
	}

	void NativeScriptManager::OnUpdate(Time t)
	{
		/*for (auto& [uuid, script] : s_scripts)
		{
			if (script->isUpdating())
				script->onUpdate(t);
		}*/
	}
}