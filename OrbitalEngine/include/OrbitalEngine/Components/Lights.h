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

namespace YAML
{
	template<>
	struct convert<Orbital::DirectionalLight>
	{
		static Node encode(const Orbital::DirectionalLight& dirLight)
		{
			Node node;
			node["Direction"] = dirLight.Direction;
			node["Ambient"] = dirLight.Ambient;
			node["Diffuse"] = dirLight.Diffuse;
			node["Specular"] = dirLight.Specular;
			return node;
		}

		static bool decode(const Node& node, Orbital::DirectionalLight& dirLight)
		{
			dirLight.Direction = node["Direction"].as<Orbital::Vec3>();
			dirLight.Ambient = node["Ambient"].as<Orbital::Vec3>();
			dirLight.Diffuse = node["Diffuse"].as<Orbital::Vec3>();
			dirLight.Specular = node["Specular"].as<Orbital::Vec3>();
			return true;
		}
	};

	template<>
	struct convert<Orbital::PointLight>
	{
		static Node encode(const Orbital::PointLight& pointLight)
		{
			Node node;
			node["Ambient"] = pointLight.Ambient;
			node["Diffuse"] = pointLight.Diffuse;
			node["Specular"] = pointLight.Specular;
			node["ConstantAttenuation"] = pointLight.ConstantAttenuation;
			node["LinearAttenuation"] = pointLight.LinearAttenuation;
			node["QuadraticAttenuation"] = pointLight.QuadraticAttenuation;
			return node;
		}

		static bool decode(const Node& node, Orbital::PointLight& pointLight)
		{
			pointLight.Ambient = node["Ambient"].as<Orbital::Vec3>();
			pointLight.Diffuse = node["Diffuse"].as<Orbital::Vec3>();
			pointLight.Specular = node["Specular"].as<Orbital::Vec3>();
			pointLight.ConstantAttenuation = node["ConstantAttenuation"].as<float>();
			pointLight.LinearAttenuation = node["LinearAttenuation"].as<float>();
			pointLight.QuadraticAttenuation = node["QuadraticAttenuation"].as<float>();
			return true;
		}
	};

	template<>
	struct convert<Orbital::SpotLight>
	{
		static Node encode(const Orbital::SpotLight& spotLight)
		{
			Node node;
			node["Direction"] = spotLight.Direction;
			node["Ambient"] = spotLight.Ambient;
			node["Diffuse"] = spotLight.Diffuse;
			node["Specular"] = spotLight.Specular;
			node["ConstantAttenuation"] = spotLight.ConstantAttenuation;
			node["LinearAttenuation"] = spotLight.LinearAttenuation;
			node["QuadraticAttenuation"] = spotLight.QuadraticAttenuation;
			node["Cutoff"] = spotLight.Cutoff;
			node["Edge"] = spotLight.Edge;
			return node;
		}

		static bool decode(const Node& node, Orbital::SpotLight& spotLight)
		{
			spotLight.Direction = node["Direction "].as<Orbital::Vec3>();
			spotLight.Ambient = node["Ambient"].as<Orbital::Vec3>();
			spotLight.Diffuse = node["Diffuse"].as<Orbital::Vec3>();
			spotLight.Specular = node["Specular"].as<Orbital::Vec3>();
			spotLight.ConstantAttenuation = node["ConstantAttenuation"].as<float>();
			spotLight.LinearAttenuation = node["LinearAttenuation"].as<float>();
			spotLight.QuadraticAttenuation = node["QuadraticAttenuation"].as<float>();
			spotLight.Cutoff = node["Cutoff"].as<float>();
			spotLight.Edge = node["Edge"].as<float>();
			return true;
		}
	};
}