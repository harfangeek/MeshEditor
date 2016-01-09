#include "Model\Vertex.h"
#include "Model\HalfEdge.h"
#include "Model\Face.h"
#include <vector>

using namespace Model;
using namespace glm;

Vertex::Vertex()
{
	originOf = NULL;
}

Vertex::~Vertex()
{
}

void Vertex::ListFaces(std::vector<Face*> &faces)
{
	faces.clear();
	if (originOf != NULL)
	{
		HalfEdge* e = originOf;
		vec3 normal;

		do
		{
			faces.push_back(e->adjacentFace);
			e = e->prev->twin;
		} while (e != originOf);
	}
}

int Vertex::CountFaces()
{
	std::vector<Face*> faces;
	ListFaces(faces);
	return faces.size();
}

void Vertex::ComputeNormal()
{	
	std::vector<Face*> faces;
	ListFaces(faces);
	vec3 sum;

	for (unsigned int i = 0; i < faces.size(); i++)
		sum += faces[i]->normal;

	sum /= faces.size();
	normal = normalize(sum);
}