#pragma once

namespace Orbital
{
	template<typename T>
	using Ref = std::shared_ptr<T>;

	template<typename T>
	using WeakRef = std::weak_ptr<T>;

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T, typename ...Args>
	inline Scope<T> CreateScope(Args... args) {
		return std::make_unique<T>(args...);
	}

	template<typename T, typename ...Args>
	inline Ref<T> CreateRef(Args... args) {
		return std::make_shared<T>(args...);
	}

	inline bool FileExists(const std::string& name)
	{
		std::ifstream ifile;
		ifile.open(name);
		if (ifile) {
			return true;
		}
		else {
			return false;
		}
	}

	using Vec2 = glm::vec2;
	using Vec3 = glm::vec3;
	using Vec4 = glm::vec4;
	using Mat3 = glm::mat3;
	using Mat4 = glm::mat4;
	using LayerID = unsigned char;
}

namespace YAML
{
	template<>
	struct convert<Orbital::Vec2>
	{
		static Node encode(const Orbital::Vec2& vec)
		{
			Node node;
			node.push_back(vec.x);
			node.push_back(vec.y);
			return node;
		}

		static bool decode(const Node& node, Orbital::Vec2& vec)
		{
			if (!node.IsSequence() || node.size() != 2) {
				return false;
			}

			vec.x = node[0].as<float>();
			vec.y = node[1].as<float>();

			return true;
		}
	};

	template<>
	struct convert<Orbital::Vec3>
	{
		static Node encode(const Orbital::Vec3& vec)
		{
			Node node;
			node.push_back(vec.x);
			node.push_back(vec.y);
			node.push_back(vec.z);
			return node;
		}

		static bool decode(const Node& node, Orbital::Vec3& vec)
		{
			if (!node.IsSequence() || node.size() != 3) {
				return false;
			}

			vec.x = node[0].as<float>();
			vec.y = node[1].as<float>();
			vec.z = node[2].as<float>();

			return true;
		}
	};
}
