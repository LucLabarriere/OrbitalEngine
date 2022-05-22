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
		void bind() const;
		WeakRef<Shader> getShader() const;

		float& getAmbient() { return m_ambient; }
		Vec3& getDiffuseTint() { return m_diffuseTint; }
		Vec3& getSpecularTint() { return m_specularTint; }
		float& getShininess() { return m_shininess; }

	private:
		Material(const std::string& tag);
		Material(const std::string& tag, const std::string& diffuseMapName);
		Material(const std::string& tag, const std::string& diffuseMapName, const std::string& specularMapName);

		inline static Ref<Material> Create(const std::string& tag)
			{ return Ref<Material>(new Material(tag)); }
		inline static Ref<Material> Create(const std::string& tag, const std::string& diffuseMapName)
			{ return Ref<Material>(new Material(tag, diffuseMapName)); }
		inline static Ref<Material> Create(const std::string& tag, const std::string& diffuseMapName, const std::string& specularMapName)
			{ return Ref<Material>(new Material(tag, diffuseMapName, specularMapName)); }

	private:
		friend MaterialManager;

		WeakRef<Shader> m_shader;

		float m_ambient = 1.0f;
		Ref<Texture> m_diffuseMap;
		Vec3 m_diffuseTint = { 1.0f, 1.0f, 1.0f };
		Ref<Texture> m_specularMap;
		Vec3 m_specularTint = { 1.0f, 1.0f, 1.0f };
		float m_shininess = 32.0f;

		static inline size_t s_id = 0;
	};
}
