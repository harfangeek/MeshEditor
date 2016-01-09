#include "HalfEdge.h"
#include "Vertex.h"
#include "Face.h"

using namespace Model;
using namespace glm;

HalfEdge::HalfEdge()
{
	Vertex* source = NULL;
	HalfEdge* next = NULL;
	HalfEdge* prev = NULL;
	HalfEdge* twin = NULL;
	Face* adjacentFace = NULL;
}

HalfEdge::~HalfEdge()
{

}

double HalfEdge::GetLength()
{
	vec3 p1 = source->position;
	vec3 p2 = next->source->position;
	return (p1 - p2).length();
}