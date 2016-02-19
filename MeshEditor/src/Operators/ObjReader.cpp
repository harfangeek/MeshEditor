#include "Operators\ObjReader.h"
#include "Operators\MeshConverter.h"
#include <iostream>
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

void ObjReader::LoadMesh(std::string fileName, Model::Mesh* &mesh, bool check)
{
	vector<glm::vec3> vertices;
	vector<vector<unsigned int>> faces;
	Operators::ObjReader::Read(fileName, vertices, faces);
	Model::Mesh* newMesh = new Model::Mesh();
	Operators::MeshConverter::ArrayToHalfEdgeStructure(newMesh, vertices, faces);

	if (check)
	{
		vector<string> errors;
		newMesh->Check(errors);
		for (unsigned int i = 0; i < errors.size(); i++)
			cout << errors[i].c_str() << endl;
	}

	mesh = newMesh;
}
