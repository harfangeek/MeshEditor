#include "Model\Face.h"
#include "Model\Vertex.h"
#include "Model\HalfEdge.h"

using namespace Model;
using namespace glm;

Face::Face()
{
	adjacentHalfEdge = NULL;
}

Face::~Face()
{

}


void Face::ComputeNormal()
{
	vec3 p1 = adjacentHalfEdge->prev->source->position;
	vec3 p2 = adjacentHalfEdge->source->position;
	vec3 p3 = adjacentHalfEdge->next->source->position;

	normal = cross(p3 - p2, p1 - p2);
	normal = normalize(normal);
}

void Face::ListHalfEdges(std::vector<HalfEdge*> &halfEdges)
{
	halfEdges.clear();
	if (adjacentHalfEdge != NULL)
	{
		halfEdges.push_back(adjacentHalfEdge);
		HalfEdge* currHalgedge = adjacentHalfEdge->next;

		while (currHalgedge != adjacentHalfEdge)
		{
			halfEdges.push_back(currHalgedge);
			currHalgedge = currHalgedge->next;
		}
	}
}

int Face::CountHalfEdges()
{
	std::vector<HalfEdge*> halfEdges;
	ListHalfEdges(halfEdges);
	return halfEdges.size();
}

void Face::ListVertices(std::vector<Vertex*> &vertices)
{
	std::vector<HalfEdge*> halfEdges;
	ListHalfEdges(halfEdges);
	vertices.clear();
	for (unsigned int i = 0; i < halfEdges.size(); i++)
		vertices.push_back(halfEdges[i]->source);
}

int Face::CountVertices()
{
	std::vector<Vertex*> vertices;
	ListVertices(vertices);
	return vertices.size();
}

void Face::ListNeighbourFaces(std::vector<Face*> &faces)
{
	std::vector<HalfEdge*> halfEdges;
	ListHalfEdges(halfEdges);
	faces.clear();
	for (unsigned int i = 0; i < halfEdges.size(); i++)
		faces.push_back(halfEdges[i]->twin->adjacentFace);
}

int Face::CountNeighbourFaces()
{
	std::vector<Face*> faces;
	ListNeighbourFaces(faces);
	return faces.size();
}
