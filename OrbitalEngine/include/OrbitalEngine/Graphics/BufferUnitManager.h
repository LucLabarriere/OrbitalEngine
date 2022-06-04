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

		void RegisterMesh(const MeshRenderer& mr, Transform& t);
		void RenderUnits();
		void Push(WeakRef<Mesh>& mesh);
		void Push(WeakRef<Material>& material, bool fill = true);

		UnitTree mUnits;
		RenderDataTree mData;
		int mCurrentIndex = 0;
	};
}
	
