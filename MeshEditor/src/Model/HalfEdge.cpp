#include "HalfEdge.h"

using namespace Model;

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

}