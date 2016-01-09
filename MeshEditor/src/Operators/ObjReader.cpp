#include "Operators\ObjReader.h"
#include <fstream>
#include <sstream>
#include <string>

using namespace Operators;
using namespace std;

bool ObjReader::Read(std::string fileName, std::vector<glm::vec3> &vertices, std::vector<std::vector<unsigned int>> &faces)
{
	vertices.clear();
	faces.clear();
	ifstream file(fileName);
	if (!file)
		return false;

	string line, type, tmp;
	while (getline(file, line))
	{
		stringstream stream(line);
		stream >> type;
		if (type == "v")
		{
			float x, y, z;
			stream >> x >> y >> z;
			vertices.push_back(glm::vec3(x, y, z));
		}
		else if (type == "f")
		{
			vector<unsigned int> indices;
			int index;
			while (stream >> tmp)
			{
				index = (unsigned int)(stoi(tmp.substr(0, tmp.find("/"))) - 1);
				indices.push_back(index);
			}
			faces.push_back(indices);
		}
	}

	return true;
}
