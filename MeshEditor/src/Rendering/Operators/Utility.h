#pragma once

//#include <experimental/filesystem>
//#include <filesystem>

#include <string>

namespace Rendering
{
	namespace Operators
	{
		class Utility
		{
		public:
			// Open the file at the given path, read its full contents into contents
			// @param path : the file path
			// @param contents : ref on a NULL pointer, will be allocated
			// @return contents size
			static size_t GetFileContents(const std::string &path, char*& contents);
			static void WriteFileContents(const std::string &path, const std::string& contents);
		};
	}
}