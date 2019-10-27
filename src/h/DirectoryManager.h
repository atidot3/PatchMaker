#pragma once

#include <iostream>
#include <vector>
#include <filesystem>
#include <fstream>

class DirectoryManager final
{
public:
	struct DirectoryCompared
	{
		DirectoryCompared()
		{
		};
		std::vector<std::string> newFiles;
		std::vector<std::string> deleteFiles;
		std::vector<std::string> compareFiles;
	};
public:
	DirectoryManager(const std::string& workDirectory);
	~DirectoryManager();

	std::vector<std::string> Parse(const std::string& path);

	static std::vector<std::string> GetSameFile(std::vector<std::string>& newFolder, std::vector<std::string>& oldFolder, const std::string& newFolderBasePath, const std::string& oldFolderBasePath)
	{
		std::vector<std::string> same;

		// -- get same files
		{
			for (auto& t : oldFolder)
			{
				for (auto& r : newFolder)
				{
					if (t == r)
					{
						if (!compare(newFolderBasePath + t, oldFolderBasePath + r))
						{
							// -- Set this file for compare data as the content is not the same
							same.emplace_back(t);
						}
					}
				}
			}
		}

		// -- remove same files from both vector
		{
			for (auto& t : same)
			{
				for (auto it = oldFolder.begin(); it != oldFolder.end(); ++it)
				{
					if (*it == t)
					{
						oldFolder.erase(it);
						break;
					}
				}
				for (auto its = newFolder.begin(); its != newFolder.end(); ++its)
				{
					if (*its == t)
					{
						newFolder.erase(its);
						break;
					}
				}
			}
		}

		return same;
	}
	static std::vector<std::string> GetOldFile(std::vector<std::string>& newFolder, std::vector<std::string>& oldFolder, const std::string& newFolderBasePath, const std::string& oldFolderBasePath)
	{
		std::vector<std::string> old;

		// -- and deleted files
		{
			for (auto t = oldFolder.begin(); t != oldFolder.end(); ++t)
			{
				bool found = false;
				for (auto it = newFolder.begin(); it != newFolder.end(); ++it)
				{
					if (*it == *t)
					{
						found = true;
						break;
					}
				}
				if (!found)
				{
					old.push_back(*t);
				}
			}
		}

		return old;
	}
	static std::vector<std::string> GetNewFile(std::vector<std::string>& newFolder, std::vector<std::string>& oldFolder, const std::string& newFolderBasePath, const std::string& oldFolderBasePath)
	{
		std::vector<std::string> _new;

		// -- now lets fine new files
		{
			for (auto t = newFolder.begin(); t != newFolder.end(); ++t)
			{
				bool found = false;
				for (auto it = oldFolder.begin(); it != oldFolder.end(); ++it)
				{
					if (*it == *t)
					{
						found = true;
						break;
					}
				}
				if (!found)
				{
					_new.push_back(*t);
				}
			}
		}

		return _new;
	}

private:
	static bool compare(const std::string& p1, const std::string& p2)
	{
		std::ifstream f1(p1, std::ifstream::binary | std::ifstream::ate);
		std::ifstream f2(p2, std::ifstream::binary | std::ifstream::ate);

		if (f1.fail() || f2.fail())
		{
			return false; //file problem
		}

		if (f1.tellg() != f2.tellg())
		{
			return false; //size mismatch
		}

		//seek back to beginning and use std::equal to compare contents
		f1.seekg(0, std::ifstream::beg);
		f2.seekg(0, std::ifstream::beg);
		return std::equal(std::istreambuf_iterator<char>(f1.rdbuf()),
			std::istreambuf_iterator<char>(),
			std::istreambuf_iterator<char>(f2.rdbuf()));
	}
private:
	const std::string& _workDirectory;
	std::vector<std::string> files;
};