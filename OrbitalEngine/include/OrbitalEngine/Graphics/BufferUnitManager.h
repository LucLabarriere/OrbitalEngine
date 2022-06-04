#pragma once

#include "OrbitalEngine/Utils.h"
#include "OrbitalEngine/Graphics/BufferUnit.h"
#include "OrbitalEngine/Components/Transform.h"

namespace Orbital
{
	class BufferUnitManager
	{
	private:
		struct RenderData
		{
			const Transform* transform;
			const Vec2& texCoordsMultiplicator;
			size_t materialId;
			size_t meshId;
		};

		using UnitTree = std::unordered_map<size_t, std::unordered_map<size_t, Ref<BufferUnit>>>;
		using RenderDataTree = std::unordered_map<size_t, std::unordered_map<size_t, std::vector<Ref<RenderData>>>>;

	public:
		BufferUnitManager();

		void registerMesh(const MeshRenderer& mr, Transform& t);
		void renderUnits();
		void push(WeakRef<Mesh>& mesh);
		void push(WeakRef<Material>& material, bool fill = true);

		UnitTree m_units;
		RenderDataTree m_data;
		int m_currentIndex = 0;
	};
}
	
