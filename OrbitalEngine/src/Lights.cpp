#include "OrbitalEngine/Components.h"
#include "OrbitalEngine/Utils.h"
#include "OrbitalEngine/Graphics.h"

#define OE_UNIFORM_LIGHT(STR1, STR2, VAR) (std::string(#STR1"[") + lightIdStr + "]."#STR2).c_str(), VAR

namespace Orbital
{
	void DirectionalLight::Bind(const Ref<Shader>& shader, unsigned int lightId)
	{
		std::string lightIdStr = std::to_string(lightId);
		shader->SetUniform3f(OE_UNIFORM_LIGHT(u_DirectionalLights, Direction, Direction));
		shader->SetUniform3f(OE_UNIFORM_LIGHT(u_DirectionalLights, Ambient, Ambient));
		shader->SetUniform3f(OE_UNIFORM_LIGHT(u_DirectionalLights, Diffuse, Diffuse));
		shader->SetUniform3f(OE_UNIFORM_LIGHT(u_DirectionalLights, Specular, Specular));
	}

	void PointLight::Bind(const Ref<Shader>& shader, unsigned int lightId)
	{
		std::string lightIdStr = std::to_string(lightId);
		shader->SetUniform3f(OE_UNIFORM_LIGHT(u_PointLights, Position, *Position));
		shader->SetUniform3f(OE_UNIFORM_LIGHT(u_PointLights, Ambient, Ambient));
		shader->SetUniform3f(OE_UNIFORM_LIGHT(u_PointLights, Diffuse, Diffuse));
		shader->SetUniform3f(OE_UNIFORM_LIGHT(u_PointLights, Specular, Specular));
		shader->SetUniform1f(OE_UNIFORM_LIGHT(u_PointLights, Constant, ConstantAttenuation));
		shader->SetUniform1f(OE_UNIFORM_LIGHT(u_PointLights, Linear, LinearAttenuation));
		shader->SetUniform1f(OE_UNIFORM_LIGHT(u_PointLights, Quadratic, QuadraticAttenuation));
	}

	void SpotLight::Bind(const Ref<Shader>& shader, unsigned int lightId)
	{
		std::string lightIdStr = std::to_string(lightId);
		shader->SetUniform3f(OE_UNIFORM_LIGHT(u_SpotLights, Position, *Position));
		shader->SetUniform3f(OE_UNIFORM_LIGHT(u_SpotLights, Direction, -glm::normalize(Direction)));
		shader->SetUniform3f(OE_UNIFORM_LIGHT(u_SpotLights, Ambient, Ambient));
		shader->SetUniform3f(OE_UNIFORM_LIGHT(u_SpotLights, Diffuse, Diffuse));
		shader->SetUniform3f(OE_UNIFORM_LIGHT(u_SpotLights, Specular, Specular));
		shader->SetUniform1f(OE_UNIFORM_LIGHT(u_SpotLights, Constant, ConstantAttenuation));
		shader->SetUniform1f(OE_UNIFORM_LIGHT(u_SpotLights, Linear, LinearAttenuation));
		shader->SetUniform1f(OE_UNIFORM_LIGHT(u_SpotLights, Quadratic, QuadraticAttenuation));
		shader->SetUniform1f(OE_UNIFORM_LIGHT(u_SpotLights, CutOff, Cutoff));
		shader->SetUniform1f(OE_UNIFORM_LIGHT(u_SpotLights, OuterCutOff, Cutoff - Cutoff * Edge / 100.0f));
	}
}
