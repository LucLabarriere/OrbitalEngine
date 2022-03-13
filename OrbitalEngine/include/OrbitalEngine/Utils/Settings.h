#pragma once

namespace OrbitalEngine
{
	enum class SettingType
	{
		Float,
		UInt,
		Bool
	};

	union SettingValue
	{
		float Float;
		unsigned int UInt;
		bool Bool;
	};

	struct Setting
	{
		SettingType Type;
		SettingValue Value;
	};

	class Settings
	{
	public:
		static void Initialize() { s_instance = new Settings; }
		enum class FloatSetting
		{
			FOV = 0,
			AspectRatio,
			_Size
		};

		enum class UIntSetting
		{
			WindowWidth = 0 + (size_t)FloatSetting::_Size,
			WindowHeight,
			RenderingAreaWidth,
			RenderingAreaHeight,
			_Size
		};

		enum class BoolSetting
		{
			VSyncEnabled = 0 + (size_t)UIntSetting::_Size,
			_Size
		};

		static inline float& Get(FloatSetting name) { return s_instance->m_settings[(size_t)name].Value.Float; }
		static inline unsigned int& Get(UIntSetting name) { return s_instance->m_settings[(size_t)name].Value.UInt; }
		static inline bool& Get(BoolSetting name) { return s_instance->m_settings[(size_t)name].Value.Bool; }
		static inline std::string GetAssetsFolder()
		{
			std::filesystem::path assets("assets");
			std::filesystem::path basepath = std::filesystem::path(__FILE__).parent_path().parent_path().parent_path().parent_path();
			std::filesystem::path absolutePath = basepath / assets;
			return absolutePath.string();
		}

		static inline std::string GetAssetPath(const std::string& relativePathString)
		{
			std::filesystem::path relativePath(relativePathString);
			std::string assetFolder = GetAssetsFolder();
			std::filesystem::path assetsFolderPath(assetFolder);

			return (assetsFolderPath / relativePath).string();
		}

	private:
		Settings() : m_settings((size_t)BoolSetting::_Size)
		{
			// Float
			m_settings[(size_t)FloatSetting::FOV] = { SettingType::Float, { .Float = 80.0f} };

			// UInt
			m_settings[(size_t)UIntSetting::WindowWidth] = { SettingType::UInt, { .UInt = 1600 } };
			m_settings[(size_t)UIntSetting::WindowHeight] = { SettingType::UInt, { .UInt = 900 } };
			m_settings[(size_t)UIntSetting::RenderingAreaWidth] = { SettingType::UInt, {.UInt = 1600 } };
			m_settings[(size_t)UIntSetting::RenderingAreaHeight] = { SettingType::UInt, {.UInt = 900 } };

			// Bool
			m_settings[(size_t)BoolSetting::VSyncEnabled] = { SettingType::Bool, { .Bool = true } };
		}

	private:
		static inline Settings* s_instance = nullptr;
		std::vector<Setting> m_settings;
	};
}



