#include "OrbitalEngine/Graphics/TextureManager.h"
#include "vendor/stb_image.h"

namespace OrbitalEngine
{
	bool TextureManager::load(const std::string& name, const std::string& filepath)
	{
		TextureData texData = Texture::Load(filepath);
		if (texData.data == nullptr)
			return false;

		Ref<Texture> texture(Texture::Create(name, texData));

		m_textures.push_back(texture);
		stbi_image_free(texData.data);

		return true;
	}
}