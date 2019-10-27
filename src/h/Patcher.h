#pragma once

#include <iostream>
#include <vector>

class Patcher final
{
public:
	static std::vector<unsigned char> Compare(const std::string& newFile, const std::string& oldFile);

private:

};