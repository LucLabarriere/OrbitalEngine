#pragma once

#include "OrbitalEngine/Utils.h"
#include "OrbitalEngine/Graphics.h"

namespace Orbital
{
	namespace Components
	{
		struct DirectionalLight
		{
			Vec3 Direction = { 0.1f, -1.0f, 0.1f };
			Vec3 Ambient = { 0.3f, 0.3f, 0.3f };
			Vec3 Diffuse = { 1.0f, 1.0f, 1.0f };
			Vec3 Specular = { 1.0f, 1.0f, 1.0f };

			void bind(const Ref<Shader>& shader, unsigned int lightId)
			{
				shader->setUniform3f(fmt::format("u_DirectionalLights[{}].Direction", lightId).c_str(), Direction);
				shader->setUniform3f(fmt::format("u_DirectionalLights[{}].Ambient", lightId).c_str(), Ambient);
				shader->setUniform3f(fmt::format("u_DirectionalLights[{}].Diffuse", lightId).c_str(), Diffuse);
				shader->setUniform3f(fmt::format("u_DirectionalLights[{}].Specular", lightId).c_str(), Specular);
			}
		};

		struct PointLight
		{
			Vec3* Position = nullptr;
			Vec3 Ambient = { 0.3f, 0.3f, 0.3f };
			Vec3 Diffuse = { 1.0f, 1.0f, 1.0f };
			Vec3 Specular = { 1.0f, 1.0f, 1.0f };
			float ConstantAttenuation = 1.0f;
			float LinearAttenuation = 0.1f;
			float QuadraticAttenuation = 2.0f;

			void bind(const Ref<Shader>& shader, unsigned int lightId)
			{
				shader->setUniform3f(fmt::format("u_PointLights[{}].Position", lightId).c_str(), *Position);
				shader->setUniform3f(fmt::format("u_PointLights[{}].Ambient", lightId).c_str(), Ambient);
				shader->setUniform3f(fmt::format("u_PointLights[{}].Diffuse", lightId).c_str(), Diffuse);
				shader->setUniform3f(fmt::format("u_PointLights[{}].Specular", lightId).c_str(), Specular);
				shader->setUniform1f(fmt::format("u_PointLights[{}].Constant", lightId).c_str(), ConstantAttenuation);
				shader->setUniform1f(fmt::format("u_PointLights[{}].Linear", lightId).c_str(), LinearAttenuation);
				shader->setUniform1f(fmt::format("u_PointLights[{}].Quadratic", lightId).c_str(), QuadraticAttenuation);
			}
		};

		struct SpotLight
		{
			Vec3* Position = nullptr;
			Vec3 Direction = { 0.0f, 0.0f, -1.0f };
			Vec3 Ambient = { 0.3f, 0.3f, 0.3f };
			Vec3 Diffuse = { 1.0f, 1.0f, 1.0f };
			Vec3 Specular = { 1.0f, 1.0f, 1.0f };
			float ConstantAttenuation = 1.0f;
			float LinearAttenuation = 0.1f;
			float QuadraticAttenuation = 2.0f;
			float Cutoff = 0.3f;
			float Edge = 1.0f;

			void bind(const Ref<Shader>& shader, unsigned int lightId)
			{
				shader->setUniform3f(fmt::format("u_SpotLights[{}].Position", lightId).c_str(), *Position);
				shader->setUniform3f(fmt::format("u_SpotLights[{}].Direction", lightId).c_str(), - glm::normalize(Direction));
				shader->setUniform3f(fmt::format("u_SpotLights[{}].Ambient", lightId).c_str(), Ambient);
				shader->setUniform3f(fmt::format("u_SpotLights[{}].Diffuse", lightId).c_str(), Diffuse);
				shader->setUniform3f(fmt::format("u_SpotLights[{}].Specular", lightId).c_str(), Specular);
				shader->setUniform1f(fmt::format("u_SpotLights[{}].Constant", lightId).c_str(), ConstantAttenuation);
				shader->setUniform1f(fmt::format("u_SpotLights[{}].Linear", lightId).c_str(), LinearAttenuation);
				shader->setUniform1f(fmt::format("u_SpotLights[{}].Quadratic", lightId).c_str(), QuadraticAttenuation);
				shader->setUniform1f(fmt::format("u_SpotLights[{}].CutOff", lightId).c_str(), Cutoff);
				shader->setUniform1f(fmt::format("u_SpotLights[{}].OuterCutOff", lightId).c_str(), Cutoff - Cutoff * Edge / 100.0f);
			}
		};
	}
}
