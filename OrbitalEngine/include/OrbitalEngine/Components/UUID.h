#pragma once

// Todo remove those headers
#include <endianness.h>
#include <uuid_v4.h>
#include "OrbitalEngine/Components/Component.h"

namespace Orbital
{
	class UUID : public Component
	{
	public:
		UUID() : mUUID(sUUIDGenerator.getUUID()) { }
		UUID(const UUID& uuid) : mUUID(uuid.GetValue()) { }

		static UUID FromString(const std::string& string)
		{
			return UUID(UUIDv4::UUID::fromStrFactory(string));
		}

		const UUIDv4::UUID& GetValue() const { return mUUID; }
		void SetValue(const UUIDv4::UUID& value) { mUUID = value; }

		operator size_t() const { return mUUID.hash(); }
		size_t hash() const { return mUUID.hash(); }
		std::string ToString() const { return mUUID.str(); }

	private:
		UUID(const UUIDv4::UUID& uuid) : mUUID(uuid) { }

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
			return uuid.hash();
		}
	};
}

namespace YAML
{
	template<>
	struct convert<Orbital::UUID>
	{
		static Node encode(const Orbital::UUID& uuid)
		{
			Node node(uuid.ToString());
			return node;
		}

		static bool decode(const Node& node, Orbital::UUID& uuid)
		{
			uuid.SetValue(UUIDv4::UUID::fromStrFactory(node.as<std::string>()));
			return true;
		}
	};
}