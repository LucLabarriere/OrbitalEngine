#pragma once

#include "OrbitalEngine/Utils.h"
#include "OrbitalEngine/Graphics/Mesh.h"

namespace OrbitalEngine
{
	class MeshManager
	{
	public:
		inline static void Initialize()
		{
			m_meshes.push_back(Ref<Mesh>(Mesh::Quad()));
			m_meshes.push_back(Ref<Mesh>(Mesh::Cube()));
		}

		inline static const Ref<Mesh>& Get(const std::string& tag)
		{
			for (const auto& mesh : m_meshes)
			{
				if (mesh->getTag() == tag)
					return mesh;
			}
			OE_RAISE_SIGSEGV("Mesh: {} was not found", tag);
			return m_meshes[0];
		}

		inline static std::vector<const char*> GetAvailableMeshes()
		{
			std::vector<const char*> meshNames;
			meshNames.reserve(m_meshes.size());

			for (size_t i = 0; i < m_meshes.size(); i++)
			{
				meshNames.push_back(m_meshes[i]->getTag().c_str());
			}
			return meshNames;
		}

	private:
		inline static std::vector<Ref<Mesh>> m_meshes;
	};
}