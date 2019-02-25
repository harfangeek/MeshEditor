#include <fstream>

#include "Rendering/Operators/Utility.h"
#include <sys/stat.h>

using namespace Rendering::Operators;
using namespace std;

size_t Utility::GetFileContents(const std::string &path, char*& contents)
{
	struct stat fileStat;
	size_t fileSize = 0;
	if (stat(path.c_str(), &fileStat) == 0)
		fileSize = fileStat.st_size;

	if (fileSize == 0)
		return 0;

	ifstream file(path, ios::binary | ios::in);
	if (!file.good())
		return 0;

	auto buffSize = fileSize;
	contents = new char[buffSize +1];
	file.read(contents, buffSize);
	file.close();

	contents[buffSize] = '\0';

	return buffSize;
}

void Utility::WriteFileContents(const std::string &path, const std::string& contents)
{
	ofstream file(path, ios::binary);
	file.write(contents.c_str(), contents.size());
	file.close();
}
