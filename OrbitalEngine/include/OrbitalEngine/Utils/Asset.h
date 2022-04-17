#pragma once

namespace Orbital
{
	class Asset
	{
	public:
		size_t getId() const { return m_id; }
		const std::string& getTag() const { return m_tag; }

		void setTag(const std::string& tag) { m_tag = tag; }

	protected:
		Asset(const std::string& tag) : m_tag(tag)
		{
			m_id = s_id;
			s_id += 1;
		}

	protected:
		static inline size_t s_id = 0;
		size_t m_id;
		std::string m_tag;
	};
}