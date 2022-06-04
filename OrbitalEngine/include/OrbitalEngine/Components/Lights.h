#pragma once

#include "OrbitalEngine/Utils.h"

#define OE_UNIFORM_LIGHT(STR1, STR2, VAR) (std::string(#STR1"[") + lightIdStr + "]."#STR2).c_str(), VAR

namespace Orbital
{
	class Shader;

	struct DirectionalLight
	{
		Vec3 Direction = { -0.3f, -1.0f, -0.3f };
		Vec3 Ambient = { 0.1f, 0.1f, 0.1f };
		Vec3 Diffuse = { 1.0f, 1.0f, 0.90f };
		Vec3 Specular = { 1.0f, 1.0f, 0.90f };

		void Bind(const Ref<Shader>& shader, unsigned int lightId);
	};

	struct PointLight
	{
		Vec3* Position = nullptr;
		Vec3 Ambient = { 0.2f, 0.2f, 0.2f };
		Vec3 Diffuse = { 1.0f, 1.0f, 1.0f };
		Vec3 Specular = { 1.0f, 1.0f, 1.0f };
		float ConstantAttenuation = 1.0f;
		float LinearAttenuation = 0.1f;
		float QuadraticAttenuation = 2.0f;

		void Bind(const Ref<Shader>& shader, unsigned int lightId);
	};

	struct SpotLight
	{
		Vec3* Position = nullptr;
		Vec3 Direction = { 0.0f, 0.0f, -1.0f };
		Vec3 Ambient = { 0.1f, 0.1f, 0.1f };
		Vec3 Diffuse = { 1.0f, 1.0f, 1.0f };
		Vec3 Specular = { 1.0f, 1.0f, 1.0f };
		float ConstantAttenuation = 1.0f;
		float LinearAttenuation = 0.1f;
		float QuadraticAttenuation = 2.0f;
		float Cutoff = 0.3f;
		float Edge = 1.0f;

		void Bind(const Ref<Shader>& shader, unsigned int lightId);
	};
}
