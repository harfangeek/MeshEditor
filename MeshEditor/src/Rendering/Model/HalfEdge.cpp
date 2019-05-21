#include "Rendering/Model/HalfEdge.h"
#include "Rendering/Model/Vertex.h"
#include "Rendering/Model/Face.h"

#include "GLM/glm.hpp"

using namespace Rendering::Model;
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