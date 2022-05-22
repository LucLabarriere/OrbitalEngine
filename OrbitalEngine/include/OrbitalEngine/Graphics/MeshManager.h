#pragma once
#include "OrbitalEngine/Graphics/Mesh.h"

namespace Orbital
{
	class MeshManager : public AssetManager<Mesh>
	{
	public:
		static void Initialize();

		static std::vector<const char*> GetAvailableMeshes();
		static bool LoadMesh(const std::string filepath, const std::string& meshName);

	private:
		MeshManager();

		void push(Ref<Mesh>&& mesh);
		std::vector<const char*> getAvailableMeshes();
		std::string getUniqueTag(const std::string& tag);

		static std::string GetUniqueTag(const std::string& tag);
	};
}