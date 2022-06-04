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
	Scene::Scene() : ECS()
	{

	}

	void Scene::Initialize()
	{
		ECS::Initialize();
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

	void Scene::SetUpdating(bool value)
	{
		ECS::SetUpdating<FirstPersonController>(value);
		ECS::SetUpdating<FreeCameraController>(value);
	}

	// Rendering
	void Scene::Begin()
	{
		auto& camera = mMainCamera.GetComponent<Camera>();
		auto shader = ShaderManager::Get("Base").lock();

		shader->Bind();
		shader->SetUniform3f("u_ViewPosition", camera.GetPosition());
		shader->SetUniformMat4f("u_VPMatrix", camera.GetVPMatrix());
		shader->SetUniformMat4f("u_MMatrix", Mat4(1.0f));
		shader->SetUniform2f("u_TexCoordsMultiplicator", Vec2(1.0f));

		size_t i = 0;

		{
			for (auto& layer : mLayers)
			{
				auto view = layer->view<DirectionalLight>();

				for (auto entity : view)
				{
					auto& light = view.get<DirectionalLight>(entity);
					light.Bind(shader, i);
					i++;
				}
			}
		}
		shader->SetUniform1i("u_nDirectionalLights", i);

		i = 0;

		{
			for (auto& layer : mLayers)
			{
				auto view = layer->view<PointLight>();


				for (auto entity : view)
				{
					auto& light = view.get<PointLight>(entity);
					light.Bind(shader, i);
					i++;
				}
			}
		}
		shader->SetUniform1i("u_nPointLights", i);

		i = 0;

		{
			for (auto& layer : mLayers)
			{
				auto view = layer->view<SpotLight>();


				for (auto entity : view)
				{
					auto& light = view.get<SpotLight>(entity);
					light.Bind(shader, i);
					i++;
				}
			}
		}
		shader->SetUniform1i("u_nSpotLights", i);
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

				if (!meshRenderer.GetDrawData().hidden)
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

				if (!meshRenderer.GetDrawData().hidden)
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
				if (camera.IsMainCamera())
				{
					camera.SetAspectRatio(aspectRatio);
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
}