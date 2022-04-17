#pragma once

#include "OrbitalEngine/Utils.h"
#include "OrbitalEngine/Graphics/Mesh.h"

namespace Orbital
{
	class MeshManager : public AssetManager<Mesh>
	{
	public:
		static void Initialize()
		{
			s_instance = new MeshManager();
		}

		static std::vector<const char*> GetAvailableMeshes()
		{
			return static_cast<MeshManager*>(s_instance)->getAvailableMeshes();
		}

	private:
		MeshManager()
		{
			s_managerName = "MeshManager";
			m_assets.push_back(Mesh::Quad());
			m_assets.push_back(Mesh::Cube());
		}

		std::vector<const char*> getAvailableMeshes()
		{
			std::vector<const char*> meshNames;
			meshNames.reserve(m_assets.size());

			for (size_t i = 0; i < m_assets.size(); i++)
			{
				meshNames.push_back(m_assets[i]->getTag().c_str());
			}
			return meshNames;
		}
	};
}