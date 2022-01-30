#pragma once

namespace OrbitalEngine
{
	template<typename T>
	using Ref = std::shared_ptr<T>;

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

	inline bool fileExists(const std::string& name)
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
}
