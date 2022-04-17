#pragma once

#include "OrbitalEngine/Utils/Misc.h"
#include "OrbitalEngine/Utils/Asset.h"

namespace Orbital
{
	template <class T>
	class AssetManager
	{
	public:
		static void Terminate() { delete s_instance; }
		static AssetManager<T>* GetInstance() { return s_instance; }

		static WeakRef<T> Get(const std::string& assetName)
		{
			for (const auto& asset: s_instance->m_assets)
			{
				if (asset->getTag() == assetName)
				{
					return asset;
				}
			}

			OE_RAISE_SIGSEGV("{}: {} does not exist", s_managerName, assetName);
		}

		static WeakRef<T> Get(size_t assetId)
		{
			for (const auto& asset : s_instance->m_assets)
			{
				if (asset->getId() == assetId)
				{
					return asset;
				}
			}

			OE_RAISE_SIGSEGV("{}: {} does not exist", s_managerName, assetId);
		}

		std::vector<Ref<T>>::iterator begin() { return m_assets.begin(); }
		std::vector<Ref<T>>::iterator end() { return m_assets.end(); }

	protected:
		AssetManager<T>() { }

	protected:
		inline static std::string s_managerName = "AssetManager";
		inline static AssetManager<T>* s_instance = nullptr;
		std::vector<Ref<T>> m_assets;
	};
}
