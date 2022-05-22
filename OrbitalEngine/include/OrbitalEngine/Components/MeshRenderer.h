#pragma once
#include "OrbitalEngine/Graphics/MeshManager.h"
#include "OrbitalEngine/Graphics/MaterialManager.h"


namespace Orbital
{
	class Transform;
	class Batch;

	namespace Components
	{
		class Transform;

		class MeshRenderer
		{
		public:
			struct DrawData
			{
				bool staticDraw = false;
				bool batchDraw = true;
				bool hidden = false;

				bool operator==(const DrawData& other);
				bool operator!=(const DrawData& other);
			};

			struct BatchData
			{
				Ref<Batch> batch = nullptr;
				int vertexPointer = -1;
				int indexPointer = -1;
			};

		public:
			MeshRenderer(const std::string& meshTag, Components::Transform* transform);
			MeshRenderer(const std::string& meshTag, Components::Transform* transform, bool batchedDraw);
			MeshRenderer(
				const std::string& meshTag, Components::Transform* transform,
				bool batchedDraw, const std::string& materialName
			);

			void destroy();
			void setMesh(const std::string& tag);

			DrawData getDrawData() const;
			BatchData getBatchData() const;
			WeakRef<Material> getMaterial() const;
			WeakRef<Mesh> getMesh() const;
			Vec2& getTexCoordsMultiplicator() { return m_texCoordsMultiplicator; }
			const Vec2& getTexCoordsMultiplicator() const { return m_texCoordsMultiplicator; }

			void setBatchData(const BatchData& data);
			void resetBatchData(const BatchData& data);
			void setDrawData(const DrawData& data);
			void setHidden(bool value);
			void setMaterial(const std::string& materialTag);

		private:
			WeakRef<Mesh> m_mesh;
			WeakRef<Material> m_material;
			Components::Transform* m_transform;
			Vec2 m_texCoordsMultiplicator = { 1.0f, 1.0f };

			DrawData m_drawData;
			BatchData m_batchData;
		};
	}
}