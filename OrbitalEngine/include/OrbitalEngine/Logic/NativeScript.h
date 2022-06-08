#pragma once

#include "OrbitalEngine/Events.h"
#include "OrbitalEngine/Utils.h"
#include "OrbitalEngine/Logic/Entity.h"

namespace Orbital
{
	template <class T> struct TypeInfo;

	#define OE_TYPE_INFO(type)\
	template <>\
	struct TypeInfo<type>\
	{ static std::string GetName() { return #type; } }

	//#define REGISTER_SERIALIZE(type, var) RegisterForSerialization<type>(#var, var);

	// TODO : Add as many types as possible here
	OE_TYPE_INFO(int);
	OE_TYPE_INFO(float);

	class Member
	{
	public:
		Member(void* value, const std::string& typeName)
			: mValue(value), mType(typeName)
		{

		}

		std::string ToString() const
		{
			if (mType == "float")
				return std::to_string(*(float*)mValue);
			else if (mType == "int")
				return std::to_string(*(int*)mValue);
			else
				return "Error, type not stringifiable";
		}

	private:
		void* mValue;
		std::string mType;
	};

	class NativeScript : public Entity
	{
	public:
		NativeScript() : Entity() { }
		NativeScript(const Entity& e) : Entity(e) { OnLoad(); }
		virtual ~NativeScript() { }

		virtual void OnLoad() { };
		virtual void OnStart() { };
		virtual void OnUpdate(Time dt) { };
		virtual void OnExit() { };
		virtual bool OnKeyPressed(const KeyPressedEvent& e) { return false; };
		virtual bool OnKeyReleased(const KeyReleasedEvent& e) { return false; };
		virtual bool OnMouseMoved(const MouseMovedEvent& e) { return false; };
		virtual bool OnMouseScrolled(const MouseScrolledEvent& e) { return false; };
		virtual bool OnMouseButtonPressed(const MouseButtonPressedEvent& e) { return false; };
		virtual bool OnMouseButtonReleased(const MouseButtonReleasedEvent& e) { return false; };
		virtual bool OnWindowResized(const WindowResizedEvent& e) { return false; };

		void SetUpdating(bool value) { mUpdating = value; }
		bool IsUpdating() const { return mUpdating; }

	protected:
		template <typename T>
		void Register(const char* name, T& value)
		{
			mMembers.emplace(name, Member(&value, TypeInfo<T>::GetName()));
		}

		std::unordered_map<const char*, Member> mMembers;

	private:
		bool mUpdating = true;
	};
}