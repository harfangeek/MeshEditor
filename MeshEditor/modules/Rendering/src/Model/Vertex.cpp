#include "Rendering/Vertex.h"
#include "Rendering/HalfEdge.h"
#include "Rendering/Face.h"
#include <vector>

using namespace Rendering;
using namespace glm;

Vertex::Vertex()
{
	originOf = NULL;
}

Vertex::Vertex(const glm::vec3& pos) : position(pos), originOf(NULL)
{
}

Vertex::~Vertex()
{
}

std::vector<Face*> Vertex::ListFaces()
{
	std::vector<Face*> faces;

	if (originOf != NULL)
	{
		HalfEdge* e = originOf;
		do
		{
			faces.push_back(e->adjacentFace);
			e = e->prev->twin;
		} while (e != originOf);
	}

	return faces;
}

unsigned int Vertex::CountFaces()
{
	std::vector<Face*> faces = ListFaces();
	return (unsigned int)faces.size();
}

void Vertex::ComputeNormal()
{	
	std::vector<Face*> faces = ListFaces();
	vec3 sum(0.0f, 0.0f, 0.0f);

	for (auto face : faces)
		sum += face->normal;

	sum /= faces.size();
	normal = normalize(sum);
}
