#include "OrbitalEngine/Components.h"
#include "OrbitalEngine/Utils.h"
#include "OrbitalEngine/Graphics.h"

#define OE_UNIFORM_LIGHT(STR1, STR2, VAR) (std::string(#STR1"[") + lightIdStr + "]."#STR2).c_str(), VAR

namespace Orbital
{
	void DirectionalLight::bind(const Ref<Shader>& shader, unsigned int lightId)
	{
		std::string lightIdStr = std::to_string(lightId);
		shader->setUniform3f(OE_UNIFORM_LIGHT(u_DirectionalLights, Direction, Direction));
		shader->setUniform3f(OE_UNIFORM_LIGHT(u_DirectionalLights, Ambient, Ambient));
		shader->setUniform3f(OE_UNIFORM_LIGHT(u_DirectionalLights, Diffuse, Diffuse));
		shader->setUniform3f(OE_UNIFORM_LIGHT(u_DirectionalLights, Specular, Specular));
	}

	void PointLight::bind(const Ref<Shader>& shader, unsigned int lightId)
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

	void SpotLight::bind(const Ref<Shader>& shader, unsigned int lightId)
	{
		std::string lightIdStr = std::to_string(lightId);
		shader->setUniform3f(OE_UNIFORM_LIGHT(u_SpotLights, Position, *Position));
		shader->setUniform3f(OE_UNIFORM_LIGHT(u_SpotLights, Direction, -glm::normalize(Direction)));
		shader->setUniform3f(OE_UNIFORM_LIGHT(u_SpotLights, Ambient, Ambient));
		shader->setUniform3f(OE_UNIFORM_LIGHT(u_SpotLights, Diffuse, Diffuse));
		shader->setUniform3f(OE_UNIFORM_LIGHT(u_SpotLights, Specular, Specular));
		shader->setUniform1f(OE_UNIFORM_LIGHT(u_SpotLights, Constant, ConstantAttenuation));
		shader->setUniform1f(OE_UNIFORM_LIGHT(u_SpotLights, Linear, LinearAttenuation));
		shader->setUniform1f(OE_UNIFORM_LIGHT(u_SpotLights, Quadratic, QuadraticAttenuation));
		shader->setUniform1f(OE_UNIFORM_LIGHT(u_SpotLights, CutOff, Cutoff));
		shader->setUniform1f(OE_UNIFORM_LIGHT(u_SpotLights, OuterCutOff, Cutoff - Cutoff * Edge / 100.0f));
	}
}
