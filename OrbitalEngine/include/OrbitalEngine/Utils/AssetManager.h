#pragma once

#include "OrbitalEngine/Utils/Misc.h"
#include "OrbitalEngine/Utils/Asset.h"
#include "OrbitalEngine/Utils/Logger.h"

namespace Orbital
{
	template <class T>
	class AssetManager
	{
	public:
		static void Terminate() { delete sInstance; }
		static AssetManager<T>* GetInstance() { return sInstance; }

		static std::vector<const char*> GetAvailable()
		{
			return sInstance->GetAvailableImpl();
		}

		static WeakRef<T> Get(const std::string& assetName)
		{
			for (auto& asset : sInstance->mAssets)
			{
				if (asset->GetTag() == assetName)
				{
					return asset;
				}
			}

			OE_RAISE_SIGSEGV("{}: {} does not exist", sManagerName, assetName);
		}

		static WeakRef<T> Get(size_t assetId)
		{
			for (Ref<T>& asset : sInstance->mAssets)
			{
				if (asset->GetId() == assetId)
				{
					return asset;
				}
			}

			OE_RAISE_SIGSEGV("{}: {} does not exist", sManagerName, assetId);
		}
		
		static size_t GetCount() { return sInstance->mAssets.size(); }

		std::vector<Ref<T>>::iterator begin() { return mAssets.begin(); }
		std::vector<Ref<T>>::iterator end() { return mAssets.end(); }

		static std::string GetUniqueTag(const std::string& tag)
		{
			return sInstance->GetUniqueTagImpl(tag);
		}

	protected:
		AssetManager<T>(const std::string managerName) { sManagerName = managerName; }

		std::vector<const char*> GetAvailableImpl()
		{
			std::vector<const char*> assetNames;
			assetNames.reserve(mAssets.size());

			for (size_t i = 0; i < mAssets.size(); i++)
			{
				assetNames.push_back(mAssets[i]->GetTag().c_str());
			}

			return assetNames;
		}

		std::string GetUniqueTagImpl(const std::string& tag)
		{
			size_t count = 0;

			std::string newTag(tag);
			bool changedName = true;

			while (changedName)
			{
				changedName = false;

				for (Ref<T>& asset : mAssets)
				{
					if (newTag == asset->GetTag())
					{
						count += 1;
						newTag = tag + "_" + std::to_string(count);
						changedName = true;
					}
				}
			}

			return newTag;
		}

	protected:
		inline static std::string sManagerName = "AssetManager";
		inline static AssetManager<T>* sInstance = nullptr;
		std::vector<Ref<T>> mAssets;
	};
}
