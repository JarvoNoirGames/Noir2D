#include "SaveManager.h"
#include <iostream>

namespace Noir2D
{
	bool SaveManager::Load(const std::string& filepath)
	{
		std::ifstream file(filepath);
		if (!file.is_open())
			return false; // not an error — e.g. first launch, no config file yet

		try
		{
			file >> _data;
		}
		catch (const std::exception& e)
		{
			std::cerr << "SaveManager: failed to parse " << filepath << ": " << e.what() << std::endl;
			return false;
		}
		return true;
	}

	bool SaveManager::Save(const std::string& filepath) const
	{
		std::ofstream file(filepath);
		if (!file.is_open())
		{
			std::cerr << "SaveManager: failed to open " << filepath << " for writing" << std::endl;
			return false;
		}
		file << _data.dump(4); // pretty-printed, human-readable
		return true;
	}
}