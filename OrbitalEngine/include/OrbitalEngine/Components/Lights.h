#pragma once

#include "OrbitalEngine/Utils.h"
#include "OrbitalEngine/Graphics.h"

#define OE_UNIFORM_LIGHT(STR1, STR2, VAR) (std::string(#STR1"[") + lightIdStr + "]."#STR2).c_str(), VAR

namespace Orbital
{
	namespace Components
	{
		struct DirectionalLight
		{
			Vec3 Direction = { -0.3f, -1.0f, -0.3f };
			Vec3 Ambient = { 0.1f, 0.1f, 0.1f };
			Vec3 Diffuse = { 1.0f, 1.0f, 0.90f };
			Vec3 Specular = { 1.0f, 1.0f, 0.90f };

			void bind(const Ref<Shader>& shader, unsigned int lightId)
			{
				std::string lightIdStr = std::to_string(lightId);
				shader->setUniform3f(OE_UNIFORM_LIGHT(u_DirectionalLights, Direction, Direction));
				shader->setUniform3f(OE_UNIFORM_LIGHT(u_DirectionalLights, Ambient, Ambient));
				shader->setUniform3f(OE_UNIFORM_LIGHT(u_DirectionalLights, Diffuse, Diffuse));
				shader->setUniform3f(OE_UNIFORM_LIGHT(u_DirectionalLights, Specular, Specular));
			}
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

			void bind(const Ref<Shader>& shader, unsigned int lightId)
			{
				std::string lightIdStr = std::to_string(lightId);
				shader->setUniform3f(OE_UNIFORM_LIGHT(u_PointLights, Position, *Position));
				shader->setUniform3f(OE_UNIFORM_LIGHT(u_PointLights, Ambient, Ambient));
				shader->setUniform3f(OE_UNIFORM_LIGHT(u_PointLights, Diffuse, Diffuse));
				shader->setUniform3f(OE_UNIFORM_LIGHT(u_PointLights, Specular, Specular));
				shader->setUniform1f(OE_UNIFORM_LIGHT(u_PointLights, Constant, ConstantAttenuation));
				shader->setUniform1f(OE_UNIFORM_LIGHT(u_PointLights, Linear, LinearAttenuation));
				shader->setUniform1f(OE_UNIFORM_LIGHT(u_PointLights, Quadratic, QuadraticAttenuation));
			}
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

			void bind(const Ref<Shader>& shader, unsigned int lightId)
			{
				std::string lightIdStr = std::to_string(lightId);
				shader->setUniform3f(OE_UNIFORM_LIGHT(u_SpotLights, Position,  *Position));
				shader->setUniform3f(OE_UNIFORM_LIGHT(u_SpotLights, Direction,  - glm::normalize(Direction)));
				shader->setUniform3f(OE_UNIFORM_LIGHT(u_SpotLights, Ambient,  Ambient));
				shader->setUniform3f(OE_UNIFORM_LIGHT(u_SpotLights, Diffuse,  Diffuse));
				shader->setUniform3f(OE_UNIFORM_LIGHT(u_SpotLights, Specular,  Specular));
				shader->setUniform1f(OE_UNIFORM_LIGHT(u_SpotLights, Constant,  ConstantAttenuation));
				shader->setUniform1f(OE_UNIFORM_LIGHT(u_SpotLights, Linear,  LinearAttenuation));
				shader->setUniform1f(OE_UNIFORM_LIGHT(u_SpotLights, Quadratic,  QuadraticAttenuation));
				shader->setUniform1f(OE_UNIFORM_LIGHT(u_SpotLights, CutOff,  Cutoff));
				shader->setUniform1f(OE_UNIFORM_LIGHT(u_SpotLights, OuterCutOff,  Cutoff - Cutoff * Edge / 100.0f));
			}
		};
	}
}
