#include "OrbitalEngine/Logic.h"
#include "OrbitalEngine/Components.h"
#include "OrbitalEngine/Graphics.h"

#define OE_COPY_COMPONENT(ClassName)\
	{\
	auto var = srcLayers[i]->try_get<ClassName>(e);\
	if (var)\
		dstLayers[i]->emplace<ClassName>(e, *var);\
	}

namespace Orbital
{
	// Initializing
	Scene::Scene()
		: mMainEntity()
	{

	}

	void Scene::Initialize()
	{
		for (auto& layer : mLayers)
		{
			layer = CreateRef<entt::registry>();
		}

		mMainEntity = Entity(OE_LAST_LAYER, mLayers[OE_LAST_LAYER]->create());

		mMainEntity.AddComponent<UUID>();
		mMainEntity.AddComponent<Tag>(GetUniqueTag("Scene"));
		auto& hierarchy = mMainEntity.AddComponent<Hierarchy>(mMainEntity, Entity());
		// TODO: have a Component parent class with a static pointer to active scene

		mMainEntity.AddComponent<LayerID>(OE_LAST_LAYER);
	}

	Scene Scene::Copy(Scene& newScene)
	{
		newScene.Initialize();

		auto& srcLayers = this->mLayers;
		auto& dstLayers = newScene.mLayers;

		for (size_t i = 0; i < srcLayers.size() - 1; i++)
		{
			auto view = srcLayers[i]->view<UUID>();

			for (auto& e : view)
			{
				auto& uuid = srcLayers[i]->get<UUID>(e);
				auto& tag = srcLayers[i]->get<Tag>(e);
				auto& layer = srcLayers[i]->get<LayerID>(e);
				auto& hierarchy = srcLayers[i]->get<Hierarchy>(e);

				auto newEntity = newScene.CreateEntity(tag, layer, e);
				newEntity.GetComponent<UUID>() = uuid;
				newEntity.GetComponent<Hierarchy>() = hierarchy;

				OE_COPY_COMPONENT(Transform);
				OE_COPY_COMPONENT(MeshRenderer);
				OE_COPY_COMPONENT(DirectionalLight);
				OE_COPY_COMPONENT(PointLight);
				OE_COPY_COMPONENT(SpotLight);
				OE_COPY_COMPONENT(Camera);
				OE_COPY_COMPONENT(FirstPersonController);
				OE_COPY_COMPONENT(FreeCameraController);
			}
		}

		return newScene;
	}

	// Working on ECS
	Entity Scene::GetEntity(const Tag& tag)
	{
		for (size_t i = 0; i < mLayers.size(); i++)
		{
			auto& layer = mLayers[i];

			auto view = layer->view<Tag>();

			for (auto entity : view)
			{
				auto& otherTag = view.get<Tag>(entity);

				if (tag == otherTag)
					return Entity(i, entity);
			}
		}

		// TODO test this function in scripts
		OE_RAISE_SIGSEGV("Error, the entity {} does not exist", tag);
	}

	Entity Scene::GetEntity(const UUID& uuid)
	{
		for (size_t i = 0; i < mLayers.size(); i++)
		{
			auto& layer = mLayers[i];
			auto view = layer->view<UUID>();

			for (auto entity : view)
			{
				auto& otherUUID = view.get<UUID>(entity);

				if (uuid == otherUUID)
					return Entity(i, entity);
			}
		}

		// TODO: test this function in scripts
		OE_RAISE_SIGSEGV("Error, the entity {} does not exist", (size_t)uuid);
	}

	void Scene::DeleteEntity(const entt::entity& handle, const LayerID& layerId)
	{
		mLayers[layerId]->destroy(handle);
	}

	Entity Scene::GetSceneEntity()
	{
		return mMainEntity;
	}

	bool Scene::IsValid(const entt::entity& handle, const LayerID& layerId) const
	{
		return mLayers[layerId]->valid(handle);
	}

	Entity Scene::CreateEntity(const Tag& tag, LayerID layerId)
	{
		Entity e(layerId, mLayers[layerId]->create());

		e.AddComponent<UUID>();
		e.AddComponent<Tag>(GetUniqueTag(tag));
		auto& hierarchy = e.AddComponent<Hierarchy>(e, GetSceneEntity());

		e.AddComponent<LayerID>(layerId);
		mCreatedEntities.push_back(e);

		return e;
	}

	Entity Scene::CreateEntity(const Tag& tag, LayerID layerId, const entt::entity& handle)
	{
		Entity e(layerId, mLayers[layerId]->create(handle));

		e.AddComponent<UUID>();
		e.AddComponent<Tag>(GetUniqueTag(tag));
		auto& hierarchy = e.AddComponent<Hierarchy>(e, GetSceneEntity());

		e.AddComponent<LayerID>(layerId);
		mCreatedEntities.push_back(e);

		return e;
	}

	Entity Scene::DuplicateEntity(const Entity& e)
	{
		// TODO correct bug when copy pasting a child entity with children /
		auto& tag = e.GetComponent<Tag>();
		auto& layerId = e.GetComponent<LayerID>();
		auto& hiearchy = e.GetComponent<Hierarchy>();
		auto* transform = e.TryGetComponent<Transform>();
		auto* meshRenderer = e.TryGetComponent<MeshRenderer>();
		auto* directionalLight = e.TryGetComponent<DirectionalLight>();
		auto* pointLight = e.TryGetComponent<PointLight>();
		auto* spotLight = e.TryGetComponent<SpotLight>();

		auto newEntity = CreateEntity(tag, layerId);

		if (transform)
		{
			auto& newTransform = newEntity.AddComponent<Transform>(*transform);

			if (meshRenderer)
				newEntity.AddComponent<MeshRenderer>(*meshRenderer, &newTransform);
		}

		if (directionalLight)
			newEntity.AddComponent<DirectionalLight>(*directionalLight);

		if (pointLight)
			newEntity.AddComponent<PointLight>(*pointLight);

		if (spotLight)
			newEntity.AddComponent<SpotLight>(*spotLight);

		newEntity.GetComponent<Hierarchy>().setParent(hiearchy.getParent());

		auto& children = hiearchy.getChildren();

		for (auto& child : children)
		{
			auto newChild = DuplicateEntity(child);
			newChild.GetComponent<Hierarchy>().setParent(newEntity);
		}

		return newEntity;
	}

	void Scene::RequireDelete(const Entity& entity)
	{
		mDeleteRequired.push_back(entity);
	}

	void Scene::RenameEntity(Entity& e, const Tag& newTag)
	{
		e.GetComponent<Tag>() = GetUniqueTag(newTag, &e);
	}

	void Scene::SetUpdating(bool value)
	{
		SetUpdating<FirstPersonController>(value);
		SetUpdating<FreeCameraController>(value);
	}

	// Rendering
	void Scene::Begin()
	{
		auto& camera = mMainCamera.GetComponent<Camera>();
		auto shader = ShaderManager::Get("Base").lock();

		shader->bind();
		shader->setUniform3f("u_ViewPosition", camera.getPosition());
		shader->setUniformMat4f("u_VPMatrix", camera.getVPMatrix());
		shader->setUniformMat4f("u_MMatrix", Mat4(1.0f));
		shader->setUniform2f("u_TexCoordsMultiplicator", Vec2(1.0f));

		size_t i = 0;

		{
			for (auto& layer : mLayers)
			{
				auto view = layer->view<DirectionalLight>();

				for (auto entity : view)
				{
					auto& light = view.get<DirectionalLight>(entity);
					light.bind(shader, i);
					i++;
				}
			}
		}
		shader->setUniform1i("u_nDirectionalLights", i);

		i = 0;

		{
			for (auto& layer : mLayers)
			{
				auto view = layer->view<PointLight>();


				for (auto entity : view)
				{
					auto& light = view.get<PointLight>(entity);
					light.bind(shader, i);
					i++;
				}
			}
		}
		shader->setUniform1i("u_nPointLights", i);

		i = 0;

		{
			for (auto& layer : mLayers)
			{
				auto view = layer->view<SpotLight>();


				for (auto entity : view)
				{
					auto& light = view.get<SpotLight>(entity);
					light.bind(shader, i);
					i++;
				}
			}
		}
		shader->setUniform1i("u_nSpotLights", i);
	}

	void Scene::End()
	{
		for (auto& entity : mDeleteRequired)
		{
			entity.Destroy();
		}

		mDeleteRequired.resize(0);
		mCreatedEntities.resize(0);
	}

	void Scene::Render()
	{
		for (auto& layer : mLayers)
		{
			auto view = layer->view<Transform, MeshRenderer, Tag>();

			for (auto entity : view)
			{
				auto& transform = view.get<Transform>(entity);
				auto& meshRenderer = view.get<MeshRenderer>(entity);
				auto& tag = view.get<Tag>(entity);

				if (!meshRenderer.getDrawData().hidden)
				{
					Renderer::RegisterMesh(meshRenderer, transform);
				}
			}
		}
	}

	void Scene::OnStart()
	{
		StartScript<FirstPersonController>();
		StartScript<FreeCameraController>();
	}

	void Scene::OnLoad()
	{
		LoadScript<FirstPersonController>();
		LoadScript<FreeCameraController>();
	}

	void Scene::OnExit()
	{
		ExitScript<FirstPersonController>();
		ExitScript<FreeCameraController>();
	}

	void Scene::OnUpdate(Time dt)
	{
		UpdateScript<FirstPersonController>(dt);
		UpdateScript<FreeCameraController>(dt);

		for (auto& layer : mLayers)
		{
			auto view = layer->view<Transform, MeshRenderer, Tag>();

			for (auto entity : view)
			{
				auto& transform = view.get<Transform>(entity);
				auto& meshRenderer = view.get<MeshRenderer>(entity);
				auto& tag = view.get<Tag>(entity);

				if (!meshRenderer.getDrawData().hidden)
				{
					Renderer::RegisterMesh(meshRenderer, transform);
				}
			}
		}
	}


	// Tools
	void Scene::SetAspectRatio(float aspectRatio)
	{
		for (auto& layer : mLayers)
		{
			auto view = layer->view<Camera>();

			for (auto entity : view)
			{
				auto& camera = view.get<Camera>(entity);
				if (camera.isMainCamera())
				{
					camera.setAspectRatio(aspectRatio);
				}
			}
		}
	}

	void Scene::Serialize()
	{
		for (auto& registry : mLayers)
		{
			auto view = registry->view<Tag>();

			for (auto entity : view)
			{
				// TODO: serialize
			}
		}
	}

	std::string Scene::GetUniqueTag(const std::string& tag, Entity* entity)
	{
		// TODO: check this method, why do we use Entity* ?
		size_t count = 0;

		std::string newTag(tag);
		bool changedName = true;
		entt::entity handle = entt::null;

		if (entity)
			handle = entity->GetHandle();

		while (changedName)
		{
			changedName = false;

			for (auto& registry : mLayers)
			{
				auto view = registry->view<Tag>();
				for (auto e : view)
				{
					auto& otherTag = view.get<Tag>(e);
					if (newTag == otherTag && e != handle)
					{
						count += 1;
						newTag = tag + "_" + std::to_string(count);
						changedName = true;
					}
				}
			}
		}

		return newTag;
	}
}