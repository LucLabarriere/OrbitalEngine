#include "OrbitalEngine/Logic.h"
#include "OrbitalEngine/Components.h"

#define OE_SERIALIZE_COMPONENT(Component)\
{\
Component* c = layer->try_get<Component>(entity);\
if (c)\
	entityNode[#Component] = *c;\
}

namespace Orbital
{
	SceneManager::SceneManager()
	{

	}

	void SceneManager::NewScene(const std::string& tag)
	{
		Scene newScene(tag);
		OE::ActiveScene = &newScene;
		newScene.Initialize();
		mScenes.insert(std::make_pair(tag, std::move(newScene)));
		SetActive(tag);
	}

	SceneManager SceneManager::Copy()
	{
		SceneManager newManager;

		for (auto& [tag, scene] : mScenes)
		{
			newManager.mScenes.emplace(tag, scene.Copy());
		}

		return newManager;
	}

	void SceneManager::SetActive(const std::string& tag)
	{
		auto iterator = mScenes.find(tag);
		OE_ASSERT(iterator != mScenes.end(), "SceneManager: {} does not exist in the loaded scenes", tag);
		OE::ActiveScene = &iterator->second;
	}

	void SceneManager::SerializeActiveScene(const std::string& filepath)
	{
		YAML::Node node;

		node["Scene Tag"] = OE::ActiveScene->GetTag();
		node["Scene UUID"] = OE::ActiveScene->GetSceneEntity().GetComponent<UUID>();

		YAML::Node testNode;

		for (size_t i = 0; i < OE::ActiveScene->mLayers.size(); i++)
		{
			auto& layer = OE::ActiveScene->mLayers[i];
			YAML::Node layerNode;
			auto view = layer->view<UUID, Tag, Hierarchy>();

			for (auto& entity : view)
			{
				YAML::Node entityNode;
				auto& uuid = view.get<UUID>(entity);
				std::string uuidString = uuid.ToString();

				entityNode["Tag"] = view.get<Tag>(entity);
				entityNode["Parent"] = view.get<Hierarchy>(entity);

				OE_SERIALIZE_COMPONENT(Transform);
				OE_SERIALIZE_COMPONENT(MeshRenderer);
				OE_SERIALIZE_COMPONENT(DirectionalLight);
				OE_SERIALIZE_COMPONENT(PointLight);
				OE_SERIALIZE_COMPONENT(SpotLight);
				OE_SERIALIZE_COMPONENT(Camera);
				OE_SERIALIZE_COMPONENT(FirstPersonController);
				OE_SERIALIZE_COMPONENT(FreeCameraController);
				layerNode[uuidString] = entityNode;
			}

			node[i] = layerNode;
		}

		std::ofstream outputFile;
		// fmt format scene tag as asset file path
		outputFile.open(Settings::GetAssetPath(filepath), std::ios::out);
		outputFile << node;
		outputFile.close();
	}

	void SceneManager::DeserializeScene(const std::string& filepath)
	{
		assert(FileExists(Settings::GetAssetPath(filepath)), "SceneManager: {} does not exist", Settings::GetAssetPath(filepath));
		YAML::Node node = YAML::LoadFile(Settings::GetAssetPath(filepath));
		auto sceneTag = node["Scene Tag"].as<std::string>();
		auto sceneUUID = node["Scene UUID"].as<UUID>();

		std::unordered_map<UUID, UUID> parents;

		mScenes.emplace(sceneTag, Scene(sceneTag));
		auto& newScene = mScenes.find(sceneTag)->second;

		OE::ActiveScene = &newScene;
		newScene.Initialize();
		newScene.GetSceneEntity().GetComponent<UUID>() = sceneUUID;

		for (size_t i = 0; i < newScene.mLayers.size(); i++)
		{
			auto& layer = newScene.mLayers[i];

			for (auto entity : node[i])
			{
				UUID uuid = entity.first.as<UUID>();
				auto& components = entity.second;
				Tag tag = components["Tag"].as<Tag>();
				parents[uuid] = components["Parent"].as<UUID>();

				auto newEntity = newScene.CreateEntity(tag, i);
				newEntity.GetComponent<UUID>() = uuid;

				for (auto component : components)
				{
					if (component.first.as<std::string>() == "Transform")
					{
						newEntity.AddComponent<Transform>(component.second.as<Transform>());

					}
					else if (component.first.as<std::string>() == "MeshRenderer")
					{
						auto& newMr = newEntity.AddComponent<MeshRenderer>("Cube", newEntity.TryGetComponent<Transform>());
						
						newMr.GetDrawData().staticDraw = component.second["StaticDraw"].as<bool>();
						newMr.GetDrawData().batchDraw = component.second["BatchDraw"].as<bool>();
						newMr.GetDrawData().hidden = component.second["Hidden"].as<bool>();
						newMr.SetMaterial(component.second["Material"].as<std::string>());
						newMr.SetMesh(component.second["Mesh"].as<std::string>());
						newMr.GetTexCoordsMultiplicator() = component.second["TexCoordsMultiplicator"].as<Orbital::Vec2>();
					}
					else if (component.first.as<std::string>() == "DirectionalLight")
					{
						auto& dirLight = newEntity.AddComponent<DirectionalLight>(component.second.as<DirectionalLight>());
					}
					else if (component.first.as<std::string>() == "PointLight")
					{
						auto& pointLight = newEntity.AddComponent<PointLight>(component.second.as<PointLight>());
						pointLight.Position = &newEntity.GetComponent<Transform>().GetPosition();
					}
					else if (component.first.as<std::string>() == "SpotLight")
					{
						auto& spotLight = newEntity.AddComponent<SpotLight>(component.second.as<SpotLight>());
						spotLight.Position = &newEntity.GetComponent<Transform>().GetPosition();
					}
					else if (component.first.as<std::string>() == "Camera")
					{
						auto& newFcc = newEntity.AddComponent<Camera>(component.second.as<Camera>());
					}
					else if (component.first.as<std::string>() == "FreeCameraController")
					{
						auto translationSpeed = component.second["TranslationSpeed"].as<float>();
						auto rotationSpeed = component.second["RotationSpeed"].as<float>();
						auto zoomSpeed = component.second["ZoomSpeed"].as<float>();

						auto& newFcc = newEntity.AddComponent<FreeCameraController>();
						newFcc.SetTranslationSpeed(translationSpeed);
						newFcc.SetRotationSpeed(rotationSpeed);
						newFcc.SetZoomSpeed(zoomSpeed);
					}
					else if (component.first.as<std::string>() == "FirstPersonController")
					{
						auto translationSpeed = component.second["TranslationSpeed"].as<float>();
						auto rotationSpeed = component.second["RotationSpeed"].as<float>();
						auto zoomSpeed = component.second["ZoomSpeed"].as<float>();

						auto& newFcc = newEntity.AddComponent<FirstPersonController>();
						newFcc.SetTranslationSpeed(translationSpeed);
						newFcc.SetRotationSpeed(rotationSpeed);
						newFcc.SetZoomSpeed(zoomSpeed);
					}
				}
			}
		}

		for (auto& [entityUUID, parentUUID] : parents)
		{
			Entity::FromUUID(entityUUID).GetComponent<Hierarchy>().SetParent(parentUUID);
		}

		//mScenes[sceneTag] = std::move(newScene);

		//SetActive(sceneTag);
	}
}