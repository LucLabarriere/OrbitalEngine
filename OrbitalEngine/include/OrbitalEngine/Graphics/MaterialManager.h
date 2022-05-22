#pragma once

#include "OrbitalEngine/Graphics/Material.h"

namespace Orbital
{
	class MaterialManager : public AssetManager<Material>
	{
	public:
		static void Initialize();

	private:
		MaterialManager();

		void push(Ref<Material>&& material);
	};
}
