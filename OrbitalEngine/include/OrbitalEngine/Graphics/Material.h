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
		void Bind() const;
		WeakRef<Shader> GetShader() const;

		float& GetAmbient() { return mAmbient; }
		Vec3& GetDiffuseTint() { return mDiffuseTint; }
		Vec3& GetSpecularTint() { return mSpecularTint; }
		float& GetShininess() { return mShininess; }

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

		WeakRef<Shader> mShader;

		float mAmbient = 1.0f;
		Ref<Texture> mDiffuseMap;
		Vec3 mDiffuseTint = { 1.0f, 1.0f, 1.0f };
		Ref<Texture> mSpecularMap;
		Vec3 mSpecularTint = { 1.0f, 1.0f, 1.0f };
		float mShininess = 32.0f;

		static inline size_t sId = 0;
	};
}
