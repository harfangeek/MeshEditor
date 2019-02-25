#include "Rendering/Model/Face.h"
#include "Rendering/Model/Vertex.h"
#include "Rendering/Model/HalfEdge.h"

#include <iostream>

using namespace Rendering::Model;
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

std::vector<HalfEdge*> Face::ListHalfEdges()
{
	std::vector<HalfEdge*> halfEdges;
	halfEdges.reserve(3);

	if (adjacentHalfEdge != NULL)
	{
		halfEdges.push_back(adjacentHalfEdge);
		HalfEdge* currHalfedge = adjacentHalfEdge->next;

		while (currHalfedge != adjacentHalfEdge)
		{
			halfEdges.push_back(currHalfedge);
			currHalfedge = currHalfedge->next;
		}
	}

	return halfEdges;
}

unsigned int Face::CountHalfEdges()
{
	std::vector<HalfEdge*> halfEdges = ListHalfEdges();
	return (unsigned int)halfEdges.size();
}

std::vector<Vertex*> Face::ListVertices()
{
	std::vector<Vertex*> vertices;
	std::vector<HalfEdge*> halfEdges = ListHalfEdges();
	
	vertices.reserve(halfEdges.size());
	for (auto halfEdge : halfEdges)
		vertices.push_back(halfEdge->source);

	return vertices;
}

unsigned int Face::CountVertices()
{
	std::vector<Vertex*> vertices = ListVertices();
	return (unsigned int)vertices.size();
}

std::vector<Face*> Face::ListNeighbourFaces()
{
	std::vector<Face*> faces;
	std::vector<HalfEdge*> halfEdges = ListHalfEdges();

	faces.reserve(halfEdges.size());
	for (auto halfEdge : halfEdges)
		faces.push_back(halfEdge->twin->adjacentFace);

	return faces;
}

unsigned int Face::CountNeighbourFaces()
{
	std::vector<Face*> faces = ListNeighbourFaces();
	return (unsigned int)faces.size();
}
