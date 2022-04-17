#pragma once

#include "OrbitalEngine/Utils.h"

namespace Orbital
{
	class Texture;
	class Shader;
	class MaterialManager;

	class Material : public Asset
	{
	public:
		void bind();

		Vec3& getTint() { return m_tint; }
		float& getAmbient() { return m_ambient; }
		float& getSpecular() { return m_specular; }

	private:
		Material(const std::string& tag);
		Material(const std::string& tag, const std::string& diffuseMapName);

		inline static Ref<Material> Create(const std::string& tag)
			{ return Ref<Material>(new Material(tag)); }
		inline static Ref<Material> Create(const std::string& tag, const std::string& diffuseMapName)
			{ return Ref<Material>(new Material(tag, diffuseMapName)); }

	private:
		friend MaterialManager;

		Vec3 m_tint = { 1.0f, 1.0f, 1.0f };
		float m_ambient = 1.0f;
		float m_specular = 1.0f;
		WeakRef<Texture> m_diffuseMapId;
		WeakRef<Shader> m_shader;
	};
}
