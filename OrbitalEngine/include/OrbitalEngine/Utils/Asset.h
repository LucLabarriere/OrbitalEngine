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
		Asset(size_t id, const std::string& tag) : m_id(id), m_tag(tag) { }

	protected:
		size_t m_id;
		std::string m_tag;
	};
}