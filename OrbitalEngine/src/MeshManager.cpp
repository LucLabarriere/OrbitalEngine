#include "OrbitalEngine/Graphics.h"
#include "OrbitalEngine/Utils.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Orbital
{
	void MeshManager::Initialize()
	{
		s_instance = new MeshManager();
		LoadMesh(Settings::GetAssetPath("models/backpack/backpack.obj"), "Backpack");
	}

	bool MeshManager::LoadMesh(const std::string filepath, const std::string& meshName)
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(filepath, aiProcess_Triangulate | aiProcess_FlipUVs);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			Logger::Error("MeshManager (Assimp error): {}", importer.GetErrorString());
			return false;
		}

		size_t nVertices = 0;
		size_t nIndices = 0;

		for (size_t i = 0; i < scene->mNumMeshes; i++)
		{
			nVertices += scene->mMeshes[i]->mNumVertices;

			for (size_t j = 0; j < scene->mMeshes[i]->mNumFaces; j++)
				nIndices += scene->mMeshes[i]->mFaces[j].mNumIndices;
		}

		Logger::Info("Loading {}: {} vertices and {} indices mesh", meshName, nVertices, nIndices);

		BasicVertexContainer vertexContainer(nVertices);
		std::vector<unsigned int> rawIndices(nIndices);

		size_t vertexCount = 0;
		size_t indexCount = 0;
		size_t lastIndex = 0;

		for (size_t m = 0; m < scene->mNumMeshes; m++)
		{
			aiMesh* assimpMesh = scene->mMeshes[m];

			for (size_t i = 0; i < assimpMesh->mNumVertices; i++)
			{
				auto& p = assimpMesh->mVertices[i];  // Position
				Vec3 position = { (float)p.x, (float)p.y, (float)p.z };
				auto& n = assimpMesh->mNormals[i];  // Normal
				Vec3 normal = { (float)n.x, (float)n.y, (float)n.z };
				auto& uv = assimpMesh->mTextureCoords[0][i];  // UV
				Vec2 texCoords = { (float)uv.x, (float)uv.y };

				vertexContainer[vertexCount].position = position;
				vertexContainer[vertexCount].normal = normal;
				vertexContainer[vertexCount].texCoords = texCoords;
				vertexCount += 1;
			}

			for (size_t i = 0; i < assimpMesh->mNumFaces; i++)
			{
				aiFace face = assimpMesh->mFaces[i];

				for (size_t j = 0; j < face.mNumIndices; j++)
				{
					rawIndices[indexCount] = face.mIndices[j] + lastIndex;
					indexCount += 1;
				}
			}

			lastIndex = rawIndices[indexCount - 1] + 1;
		}
		IndexContainer indexContainer(rawIndices);
		((MeshManager*)s_instance)->push(Ref<Mesh>(new Mesh(GetUniqueTag(meshName), vertexContainer, indexContainer)));

		return true;
	}

	MeshManager::MeshManager() : AssetManager<Mesh>()
	{
		s_managerName = "MeshManager";
		push(Mesh::Quad());
		push(Mesh::Cube());
		push(Mesh::Triangle());
	}

	void MeshManager::push(Ref<Mesh>&& mesh)
	{
		m_assets.push_back(mesh);
		Renderer::PushBufferUnit(mesh);
	}

	std::string MeshManager::GetUniqueTag(const std::string& tag)
	{
		return ((MeshManager*)s_instance)->getUniqueTag(tag);
	}

	std::string MeshManager::getUniqueTag(const std::string& tag)
	{
		size_t count = 0;

		std::string newTag(tag);
		bool changedName = true;

		while (changedName)
		{
			changedName = false;

			for (auto& mesh : m_assets)
			{
				if (newTag == mesh->getTag())
				{
					count += 1;
					newTag = tag + "_" + std::to_string(count);
					changedName = true;
				}
			}
		}

		return newTag;
	}
}