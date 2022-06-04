#pragma once

#include <endianness.h>
#include <uuid_v4.h>
#include "OrbitalEngine/Components/Component.h"

namespace Orbital
{
	class UUID : public Component
	{
	public:
		UUID() : mUUID(sUUIDGenerator.getUUID())
		{
			
		}

		UUID(const UUID& uuid) : mUUID(uuid.GetValue())
		{

		}

		const UUIDv4::UUID& GetValue() const { return mUUID; }
		operator size_t() const
		{
			return mUUID.hash();
		}

	private:
		static inline UUIDv4::UUIDGenerator<std::mt19937_64> sUUIDGenerator;
		UUIDv4::UUID mUUID;
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