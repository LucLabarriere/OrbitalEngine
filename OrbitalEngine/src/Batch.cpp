#include "OrbitalEngine/Graphics/Batch.h"
#include "OrbitalEngine/Graphics/RenderCommands.h"
#include "OrbitalEngine/Components/MeshRenderer.h"
#include "OrbitalEngine/Components/Transform.h"
#include "OrbitalEngine/Utils.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace Orbital
{
	Batch::Batch(WeakRef<Material>& material, size_t vertexCount, size_t indexCount)
		: mMaterial(material)
		, mVertices(vertexCount)
		, mIndices(indexCount == 0 ? int(vertexCount - 2) * 3 : indexCount)
		, mFreeVertices(mVertices.GetCount(), true)
		, mRenderMode(OE_DYNAMIC_DRAW)
	{
		mVao = Ref<VertexArray>(VertexArray::Create());
		mVbo = Ref<VertexBuffer>(VertexBuffer::Create(mRenderMode));
		mIbo = Ref<IndexBuffer>(IndexBuffer::Create(mRenderMode));
		
		mSubDataFreeVertices.push_back(BufferSubData(0, mVertices.GetCount() - 1));
		mSubDataFreeIndices.push_back(BufferSubData(0, mIndices.GetCount() - 1));
	}

	void Batch::Bind() const
	{
		mVao->Bind();
		mIbo->Bind();
	}

	void Batch::BindMaterial() const
	{
		mMaterial.lock()->Bind();
	}

	void Batch::AllocateMemory() const
	{
		mVao->Bind();
		mVbo->Bind();
		mVbo->AllocateMemory(nullptr, mVertices.GetSize());

		mIbo->Bind();
		mIbo->AllocateMemory(nullptr, mIndices.GetSize());

		mVertices.SetLayout(*mVbo);
	}

	void Batch::SubmitData() const
	{
		mVao->Bind();
		mVbo->Bind();
		// Do submitSubData Here
		mVbo->SubmitData(mVertices.GetData(), mVertices.GetSize());

		mIbo->Bind();
		mIbo->SubmitData(mIndices.GetData(), mIndices.GetSize());
	}

	void Batch::Render()
	{
		mVao->Bind();
		mVbo->Bind();

		for (auto& subData : mSubDataVertices)
		{
			size_t stride = (subData.lastIndex - subData.firstIndex + 1);
			mVbo->submitSubData(
				mVertices.GetFirstVertex() + subData.firstIndex,
				subData.firstIndex * sizeof(BasicVertex),
				stride * sizeof(BasicVertex)
			);
		}

		mCurrentSubDataVertices = nullptr;
		mSubDataVertices.resize(0);

		mIbo->Bind();
		
		for (auto& subData : mSubDataIndices)
		{
			size_t stride = (subData.lastIndex - subData.firstIndex + 1);
			mIbo->submitSubData(
				mIndices.GetFirstIndex() + subData.firstIndex,
				subData.firstIndex * sizeof(unsigned int),
				stride * sizeof(unsigned int));
		}
		mCurrentSubDataIndices = nullptr;

		RenderCommands::DrawIndexed(OE_TRIANGLES, mIndices.GetSize());
		Metrics::IncrementBatchCount();

		mSubDataIndices.resize(0);
	}

	void Batch::RegisterMesh(MeshRenderer& mr, Transform& t)
	{
		auto mesh = mr.GetMesh().lock();
		auto& vertices = mesh->GetVertices();
		auto& indices = mesh->getIndices();
		auto drawData = mr.GetDrawData();
		auto batchData = mr.GetBatchData();

		int vertexPointer = batchData.vertexPointer;
		int indexPointer = batchData.indexPointer;

		if (vertexPointer == -1 || indexPointer == -1)
		{
			std::tie(vertexPointer, indexPointer) = GetAvailableSlot(vertices.GetCount(), indices.GetCount());

			batchData.vertexPointer = vertexPointer;
			batchData.indexPointer = indexPointer;
			batchData.batch = shared_from_this();

			mr.SetBatchData(batchData);
		}

		if (vertexPointer == -1 || indexPointer == -1)
		{
			Logger::Error("Error not enough available space, Vertex: {} Index: {}", vertexPointer, indexPointer);
			return;
		}

		glm::mat4 model(1.0f);
		model = glm::translate(model, t.GetPosition());
		model = glm::rotate(model, glm::radians(t.GetRotation()[0]), { 1.0f, 0.0f, 0.0f });
		model = glm::rotate(model, glm::radians(t.GetRotation()[1]), { 0.0f, 1.0f, 0.0f });
		model = glm::rotate(model, glm::radians(t.GetRotation()[2]), { 0.0f, 0.0f, 1.0f });
		model = glm::scale(model, t.GetScale());

		glm::mat4 rotation(0.0f);
		rotation = glm::rotate(rotation, glm::radians(t.GetRotation()[0]), { 1.0f, 0.0f, 0.0f });
		rotation = glm::rotate(rotation, glm::radians(t.GetRotation()[1]), { 0.0f, 1.0f, 0.0f });
		rotation = glm::rotate(rotation, glm::radians(t.GetRotation()[2]), { 0.0f, 0.0f, 1.0f });
		
		if (mCurrentSubDataVertices == nullptr || mCurrentSubDataVertices->lastIndex + 1 != vertexPointer)
		{
			mSubDataVertices.push_back(BufferSubData(vertexPointer, vertexPointer + vertices.GetCount() - 1));
			mCurrentSubDataVertices = &mSubDataVertices[mSubDataVertices.size() - 1];
		}
		else
		{
			mCurrentSubDataVertices->lastIndex += vertices.GetCount();
		}

		for (size_t i = 0; i < vertices.GetCount(); i++)
		{
			mVertices[i + vertexPointer] = vertices[i];
			mVertices[i + vertexPointer].position = model * Vec4(mVertices[i + vertexPointer].position, 1.0f);
			mVertices[i + vertexPointer].normal = Mat3(glm::transpose(glm::inverse(model))) * mVertices[i + vertexPointer].normal;
			mVertices[i + vertexPointer].texCoords = mr.GetTexCoordsMultiplicator() * vertices[i].texCoords;
			mFreeVertices[i + vertexPointer] = false;
		}

		if (mCurrentSubDataIndices == nullptr || mCurrentSubDataIndices->lastIndex  + 1 != indexPointer)
		{
			mSubDataIndices.push_back(BufferSubData(indexPointer, indexPointer + indices.GetCount() - 1));
			mCurrentSubDataIndices = &mSubDataIndices[mSubDataIndices.size() - 1];
		}
		else
		{
			mCurrentSubDataIndices->lastIndex += indices.GetCount();
		}

		for (size_t i = 0; i < indices.GetCount(); i++)
		{
			mIndices[i + indexPointer] = vertexPointer + indices[i];
		}

		updateFullStatus();

		t.CleanUp();
	}


	void Batch::DeleteMesh(MeshRenderer& mr)
	{
		// TODO: make it work
		auto batchData = mr.GetBatchData();
		size_t vertexPointer = batchData.vertexPointer;
		size_t indexPointer = batchData.indexPointer;
		auto mesh = mr.GetMesh().lock();

		auto& vertices = mesh->GetVertices();
		auto& indices = mesh->getIndices();

		// Updating free vertices
		for (auto& subData : mSubDataFreeVertices)
		{
			if (subData.lastIndex + 1 == vertexPointer)
			{
				subData.lastIndex += vertices.GetCount();
			}
			else if (vertexPointer + vertices.GetCount() - 1 == subData.firstIndex)
			{
				subData.firstIndex -= vertices.GetCount();
			}
		}

		// Updating free indices
		for (auto& subData : mSubDataFreeIndices)
		{
			if (subData.lastIndex + 1 == indexPointer)
			{
				subData.lastIndex += indices.GetCount();
			}
			else if (vertexPointer + indices.GetCount() - 1 == subData.firstIndex)
			{
				subData.firstIndex -= indices.GetCount();
			}
		}

		for (size_t i = vertexPointer; i < vertices.GetCount() + vertexPointer; i++)
		{
			mVertices[i] = BasicVertex::Empty();
			mFreeVertices[i] = true;
		}

		for (size_t i = indexPointer; i < indices.GetCount() + indexPointer; i++)
		{
			mIndices[i] = 0;
		}

		mSubDataVertices.push_back(BufferSubData(vertexPointer, vertexPointer + vertices.GetCount() - 1));
		mSubDataIndices.push_back(BufferSubData(indexPointer, indexPointer + indices.GetCount() - 1));

		mr.SetBatchData(MeshRenderer::BatchData());

		updateFullStatus();
	}

	bool Batch::MeshFits(MeshRenderer& mr)
	{
		auto mesh = mr.GetMesh();
		auto& vertices = mesh.lock()->GetVertices();
		auto& indices = mesh.lock()->getIndices();

		auto [vertexPointer, indexPointer] = GetAvailableSlot(vertices.GetCount(), indices.GetCount(), false);

		if (vertexPointer != -1 && indexPointer != -1)
			return true;

		return false;
	}

	std::tuple<int, int> Batch::GetAvailableSlot(size_t vertexCount, size_t indexCount, bool record)
	{
		int vertexPointer = -1;
		int indexPointer = -1;

		for (auto& subData : mSubDataFreeVertices)
		{
			if (vertexCount <= subData.GetStride())
			{
				vertexPointer = subData.firstIndex;
				if (record) subData.firstIndex += vertexCount;
				break;
			}
		}

		for (auto& subData : mSubDataFreeIndices)
		{
			if (indexCount <= subData.GetStride())
			{
				indexPointer = subData.firstIndex;
				if (record) subData.firstIndex += indexCount;
				break;
			}
		}

		return std::make_tuple(vertexPointer, indexPointer);
	}

	void Batch::updateFullStatus()
	{
		auto [ vertexPointer, indexPointer ] = GetAvailableSlot(24, 36, false);

		if (vertexPointer == -1 || indexPointer == -1)
			mFull = true;
		else
			mFull = false;
	}
}