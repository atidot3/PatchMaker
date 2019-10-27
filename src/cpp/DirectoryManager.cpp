#include <DirectoryManager.h>

namespace fs = std::filesystem;

DirectoryManager::DirectoryManager(const std::string& workDirectory)
	:_workDirectory{workDirectory}
{

}

DirectoryManager::~DirectoryManager()
{

}

void eraseAllSubStr(std::string& mainStr, const std::string& toErase)
{
	size_t pos = std::string::npos;

	// Search for the substring in string in a loop untill nothing is found
	while ((pos = mainStr.find(toErase)) != std::string::npos)
	{
		// If found then erase it from string
		mainStr.erase(pos, toErase.length());
	}
}

std::vector<std::string> DirectoryManager::Parse(const std::string& path)
{
	std::vector<std::string> files;
	for (const auto& entry : fs::directory_iterator(path))
	{
		if (entry.is_directory())
		{
			auto list = Parse(entry.path().string());
			for (auto& t : list)
			{
				std::string str = t;
				eraseAllSubStr(str, _workDirectory);
				files.emplace_back(t);
			}
		}
		if (entry.is_regular_file())
		{
			std::string str = entry.path().string();
			eraseAllSubStr(str, _workDirectory);
			files.push_back(str);
		}
	}
	return files;
}
