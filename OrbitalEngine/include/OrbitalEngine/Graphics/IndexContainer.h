#pragma once

namespace Orbital
{
	class IndexBuffer;

	class IndexContainer
	{
	public:
		IndexContainer(const std::vector<unsigned int>& indices) : m_indices(indices) { }
		IndexContainer(size_t count) : m_indices(count) { }

		void allocateMemory(const IndexBuffer& buffer) const;
		void submitData(const IndexBuffer& buffer) const;

		void setIndex(size_t i, unsigned int index) { m_indices[i] = index; }

		size_t getCount() const { return m_indices.size(); }
		size_t getSize() const { return m_indices.size() * sizeof(unsigned int); }
		const void* getData() const { return m_indices.data(); }
		const unsigned int* getFirstIndex() const { return &m_indices[0]; }
		unsigned int& operator[](size_t i) { return m_indices[i]; }
		const unsigned int& operator[](size_t i) const { return m_indices[i]; }

	private:
		std::vector <unsigned int> m_indices;
	};
}