#pragma once

#include "OrbitalEngine/Tools.h"
#include "OrbitalEngine/Mesh.h"

namespace OrbitalEngine
{
	class MeshManager
	{
	public:
		inline static void Initialize()
		{
			m_meshes.push_back(Ref<Mesh>(Mesh::Quad()));
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

	private:
		inline static std::vector<Ref<Mesh>> m_meshes;
	};
}