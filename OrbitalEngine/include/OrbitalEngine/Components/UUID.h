#pragma once

#include <endianness.h>
#include <uuid_v4.h>

namespace Orbital
{
	class UUID
	{
	public:
		UUID() : m_uuid(s_uuidGenerator.getUUID())
		{
			
		}

		UUID(const UUID& uuid) : m_uuid(uuid.getValue())
		{

		}

		const UUIDv4::UUID& getValue() const { return m_uuid; }
		operator size_t() const
		{
			return m_uuid.hash();
		}

	private:
		static inline UUIDv4::UUIDGenerator<std::mt19937_64> s_uuidGenerator;
		UUIDv4::UUID m_uuid;
	};
}

namespace std
{
	template <>
	struct hash<Orbital::UUID>
	{
		std::size_t operator()(const Orbital::UUID& uuid) const
		{
			return (size_t)uuid;
		}
	};
}