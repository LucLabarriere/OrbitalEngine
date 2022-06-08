#pragma once

#include "OrbitalEngine/Logic/ECS.h"

#define OE_CALL_NATIVE_SCRIPT_METHOD(method, ...)\
	for (auto& layer : OE::ActiveScene->mLayers)\
	{\
		auto view = layer->view<NativeScriptManager>();\
		for (auto& entity : view)\
		{\
			auto& manager = layer->get<NativeScriptManager>(entity);\
			manager.method(__VA_ARGS__);\
		}\
	}

namespace YAML
{
	class Node;
}

namespace Orbital
{
	class SceneManager
	{
	public:
		SceneManager();
		void NewScene(const std::string& tag);
		SceneManager Copy();
		//void LoadScene(const std::string& tag);
		void SetActive(const std::string& tag);
		void SerializeActiveScene(const std::string& filepath);
		void DeserializeScene(const std::string& filepath);

		void OnLoad() { OE_CALL_NATIVE_SCRIPT_METHOD(OnLoad) }
		void OnStart() { OE_CALL_NATIVE_SCRIPT_METHOD(OnStart) }
		void OnUpdate(Time dt)
		{
			OE::ActiveScene->OnUpdate(dt);
			OE_CALL_NATIVE_SCRIPT_METHOD(OnUpdate, dt)
		}
		void OnExit() { OE_CALL_NATIVE_SCRIPT_METHOD(OnExit) }
		bool OnKeyPressed(const KeyPressedEvent& e) { OE_CALL_NATIVE_SCRIPT_METHOD(OnKeyPressed, e) }
		bool OnKeyReleased(const KeyReleasedEvent& e) { OE_CALL_NATIVE_SCRIPT_METHOD(OnKeyReleased, e) }
		bool OnMouseMoved(const MouseMovedEvent& e) { OE_CALL_NATIVE_SCRIPT_METHOD(OnMouseMoved, e) }
		bool OnMouseScrolled(const MouseScrolledEvent& e) { OE_CALL_NATIVE_SCRIPT_METHOD(OnMouseScrolled, e) }
		bool OnMouseButtonPressed(const MouseButtonPressedEvent& e) { OE_CALL_NATIVE_SCRIPT_METHOD(OnMouseButtonPressed, e) }
		bool OnMouseButtonReleased(const MouseButtonReleasedEvent& e) { OE_CALL_NATIVE_SCRIPT_METHOD(OnMouseButtonReleased, e) }
		bool OnWindowResized(const WindowResizedEvent& e) { OE_CALL_NATIVE_SCRIPT_METHOD(OnWindowResized, e) }
		
		std::unordered_map<std::string, Scene>::iterator begin() { return mScenes.begin(); }
		std::unordered_map<std::string, Scene>::iterator end() { return mScenes.end(); };

	private:
		std::unordered_map<std::string, Scene> mScenes;
	};
}
