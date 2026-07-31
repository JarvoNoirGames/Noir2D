#pragma once
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>

namespace Noir2D
{
	class SaveManager
	{
	public:
		static SaveManager& GetInstance()
		{
			static SaveManager instance;
			return instance;
		}

		bool Load(const std::string& filepath);
		bool Save(const std::string& filepath) const;

		template<typename T>
		T Get(const std::string& key, const T& defaultValue) const
		{
			if (_data.contains(key))
			{
				try { return _data.at(key).get<T>(); }
				catch (...) { return defaultValue; } // wrong type in file — fall back safely
			}
			return defaultValue;
		}

		template<typename T>
		void Set(const std::string& key, const T& value)
		{
			_data[key] = value;
		}

	private:
		SaveManager() = default;
		nlohmann::json _data;
	};
}