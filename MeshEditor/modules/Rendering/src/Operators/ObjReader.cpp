#include "Rendering/ObjReader.h"
#include "Rendering/MeshConverter.h"
#include "Rendering/Utility.h"
#include "Rendering/Mesh.h"

#include <sstream>

using namespace Rendering;
using namespace std;

bool ObjReader::ReadObj(const std::string &path, std::vector<glm::vec3> &vertices, std::vector<std::vector<unsigned int>> &faces)
{
	char* contents = NULL;
	auto size = Utility::GetFileContents(path, contents);

	constexpr unsigned int sizeBuff = 40, sizeVec = 4;
	short type;
	char buff[sizeBuff];
	char* end;
	float vec[3]{ 0.0f,0.0f,0.0f };
	float component;
	unsigned int i = 0, j = 0, k = 0, index = 0;
	vector<unsigned int> indices;
	indices.reserve(sizeVec);

	j = 0;
	while (i < size)
	{
		// Get next block of the line
		k = 0;
		buff[0] = '\0';
		while (i < size && k < sizeBuff && contents[i] != ' ' && contents[i] != '\t' && contents[i] != '\n')
		{
			buff[k] = contents[i];
			k++;
			i++;
		}
		buff[k] = '\0';

		if (j == 0) // If firt block of the line, determine the line type
		{
			type = 0;
			if (buff[0] == 'v' && buff[1] == '\0')
				type = 1;
			else if (buff[0] == 'f' && buff[1] == '\0')
				type = 2;

			j++;

			if (type == 0) // Ignore the line
				while (i < size && contents[i] != '\n')
					i++;
		}
		else			
		{
			// Parse other blocks of the current line
			if (type == 1 && j < 4) // Type vertex, get next vector component
			{
				component = strtof(buff, &end);
				if (end != buff)
					vec[j-1] = component;
			}
			else if (type == 2) // Type face, get next vertex index
			{
				index = atoi(buff);
				if (index > 0)
					indices.push_back(index - 1);
			}

			j++;
		}
		
		if(contents[i] == '\n') // End of line, save results
		{
			if (type == 1 && j == 4)
				vertices.emplace_back(glm::vec3(vec[0], vec[1], vec[2]));
			else if(type == 2)
			{
				faces.push_back(move(indices));
				indices.reserve(sizeVec);
			}

			j = 0;
		}

		i++;
	}

	delete contents;

	return true;
}

bool ObjReader::WriteObj(const std::string &path, const std::vector<GLfloat>& vertices, const std::vector<GLuint>& faces)
{
	unsigned int verticesSize = static_cast<unsigned int>(vertices.size()) / 3;
	unsigned int facesSize = static_cast<unsigned int>(faces.size()) / 3;

	ostringstream oss;

	oss << "# Vertices : " << verticesSize << "\n";
	oss << "# Faces : " << facesSize << "\n";

	int i = 0;
	for(auto vertexComp : vertices)
	{
		if (i % 3 == 0)
			oss << "\nv";

		oss << " " << vertexComp;
		i++;
	}

	i = 0;
	for(auto faceComp : faces)
	{
		if (i % 3 == 0)
			oss << "\nf";

		oss << " " << (faceComp + 1);
		i++;
	}

	oss << "\n";

	Utility::WriteFileContents(path, oss.str());

	return true;
}

Mesh* ObjReader::LoadMesh(const std::string &path)
{
	vector<glm::vec3> vertices;
	vector<vector<unsigned int>> faces;
	ObjReader::ReadObj(path, vertices, faces);
	auto newMesh = new Mesh();
	MeshConverter::ArrayToHalfEdgeStructure(*newMesh, vertices, faces);

	return newMesh;
}

void ObjReader::SaveMesh(const Mesh& mesh, const std::string &path)
{
	vector<GLfloat> vertices;
	vector<GLuint> faces;
	vector<GLfloat> normals;
	MeshConverter::HalfEdgeStructureToArray(mesh, vertices, faces, normals);
	WriteObj(path, vertices, faces);
}
