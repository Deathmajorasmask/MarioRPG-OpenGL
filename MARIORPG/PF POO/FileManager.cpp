#include "FileManager.h"

FileManager::FileManager() {};
FileManager::~FileManager() {};

// return file name path
std::string FileManager::filenamePath(std::string filename) {
	WCHAR path[MAX_PATH];
	GetModuleFileNameW(NULL, path, MAX_PATH);
	char ch[260];
	char DefChar = ' ';
	WideCharToMultiByte(CP_ACP, 0, path, -1, ch, 260, &DefChar, NULL);
	std::string str(ch);
	size_t found = str.find_last_of("/\\");
	std::string pathoriginal = str.substr(0, found);
	std::string fileexecutable = str.substr(found + 1);
	std::string pathfile = pathoriginal + "\\" + filename;
	return pathfile;
}

bool FileManager::fileExists(std::string const& name)
{
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}