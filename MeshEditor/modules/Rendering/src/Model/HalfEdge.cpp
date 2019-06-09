#include "Rendering/HalfEdge.h"
#include "Rendering/Vertex.h"
#include "Rendering/Face.h"

#include "GLM/glm.hpp"

using namespace Rendering;
using namespace glm;

HalfEdge::HalfEdge()
{
	source = NULL;
	next = NULL;
	prev = NULL;
	twin = NULL;
	adjacentFace = NULL;
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