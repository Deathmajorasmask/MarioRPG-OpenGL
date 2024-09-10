#pragma once

#include<iostream>
#include <windowsx.h>
#include <cstddef>
#include <Windows.h>

class FileManager
{
private:

public:
	FileManager();
	~FileManager();

	std::string filenamePath(std::string filename);
	bool fileExists(std::string const& name);
};