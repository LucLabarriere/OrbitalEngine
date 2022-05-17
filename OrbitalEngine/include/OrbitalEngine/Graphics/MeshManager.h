#pragma once

#include "OrbitalEngine/Utils.h"
#include "OrbitalEngine/Graphics/Mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "OrbitalEngine/Utils/Settings.h"

namespace Orbital
{
	class MeshManager : public AssetManager<Mesh>
	{
	public:
		static void Initialize()
		{
			s_instance = new MeshManager();
			LoadMesh(Settings::GetAssetPath("models/backpack/backpack.obj"));
		}

		static std::vector<const char*> GetAvailableMeshes()
		{
			return static_cast<MeshManager*>(s_instance)->getAvailableMeshes();
		}

		static bool LoadMesh(const std::string filepath)
		{
			Assimp::Importer importer;
			const aiScene* scene = importer.ReadFile(filepath, aiProcess_Triangulate | aiProcess_FlipUVs);
			
			if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
			{
				Logger::Error("MeshManager (Assimp error): {}", importer.GetErrorString());
				return false;
			}

			std::vector<aiMesh*> meshes(0);
			ProcessNode(scene->mRootNode, scene);
		}

	private:
		MeshManager() : AssetManager<Mesh>()
		{
			s_managerName = "MeshManager";
			m_assets.push_back(Mesh::Quad());
			m_assets.push_back(Mesh::Cube());
			m_assets.push_back(Mesh::Triangle());
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

		static void ProcessNode(aiNode* node, const aiScene* scene)
		{
			for (size_t i = 0; i < node->mNumMeshes; i++)
			{
				((MeshManager*)s_instance)->processMesh(scene->mMeshes[node->mMeshes[i]], scene);
			}

			for (size_t i = 0; i < node->mNumChildren; i++)
			{
				ProcessNode(node->mChildren[i], scene);
			}
		}

		void processMesh(aiMesh* assimpMesh, const aiScene* scene)
		{
			BasicVertexContainer vertices(assimpMesh->mNumVertices);

			for (size_t i = 0; i < assimpMesh->mNumVertices; i++)
			{
				auto& p = assimpMesh->mVertices[i];  // Position
				Vec3 position = { (float)p.x, (float)p.y, (float)p.z };
				auto& n = assimpMesh->mNormals[i];  // Normal
				Vec3 normal = { (float)n.x, (float)n.y, (float)n.z };
				auto& uv = assimpMesh->mTextureCoords[0][i];  // UV
				Vec2 texCoords = { (float)uv.x, (float)uv.y };

				vertices[i].position = position;
				vertices[i].normal = normal;
				vertices[i].texCoords = texCoords;
			}

			std::vector<unsigned int> rawIndices(0);

			for (size_t i = 0; i < assimpMesh->mNumFaces; i++)
			{
				aiFace face = assimpMesh->mFaces[i];

				for (size_t j = 0; j < face.mNumIndices; j++)
				{
					rawIndices.push_back(face.mIndices[j]);
				}
			}

			IndexContainer indices(rawIndices);

			Ref<Mesh> newMesh = Ref<Mesh>(new Mesh(GetUniqueTag("Mesh"), vertices, indices));
			m_assets.push_back(newMesh);
		}

		static std::string GetUniqueTag(const std::string& tag)
		{
			return ((MeshManager*)s_instance)->getUniqueTag(tag);
		}

		std::string getUniqueTag(const std::string& tag)
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
	};
}