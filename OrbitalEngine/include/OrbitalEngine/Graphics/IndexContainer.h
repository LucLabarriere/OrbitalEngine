#pragma once

namespace Orbital
{
	class IndexBuffer;

	class IndexContainer
	{
	public:
		IndexContainer(const std::vector<unsigned int>& indices) : mIndices(indices) { }
		IndexContainer(size_t count) : mIndices(count) { }

		void AllocateMemory(const IndexBuffer& buffer) const;
		void SubmitData(const IndexBuffer& buffer) const;

		void SetIndex(size_t i, unsigned int index) { mIndices[i] = index; }

		size_t GetCount() const { return mIndices.size(); }
		size_t GetSize() const { return mIndices.size() * sizeof(unsigned int); }
		const void* GetData() const { return mIndices.data(); }
		const unsigned int* GetFirstIndex() const { return &mIndices[0]; }
		unsigned int& operator[](size_t i) { return mIndices[i]; }
		const unsigned int& operator[](size_t i) const { return mIndices[i]; }

	private:
		std::vector <unsigned int> mIndices;
	};
}