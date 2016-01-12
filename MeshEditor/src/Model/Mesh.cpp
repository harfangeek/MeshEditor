#include "Model\Mesh.h"
#include <sstream>

using namespace Model;

Mesh::Mesh()
{

}

Mesh::~Mesh()
{
	Clean();
}

void Mesh::Clean()
{
	for (unsigned int i = 0; i < halfEdges.size(); i++)
	{
		if (halfEdges[i] != NULL)
			delete halfEdges[i];
	}
	halfEdges.clear();

	for (unsigned int i = 0; i < vertices.size(); i++)
	{
		if (vertices[i] != NULL)
			delete vertices[i];
	}
	vertices.clear();

	for (unsigned int i = 0; i < faces.size(); i++)
	{
		if (faces[i] != NULL)
			delete faces[i];
	}
	faces.clear();
}

bool Mesh::Check(std::vector<std::string>& errors)
{
	errors.clear();	
	
	// HalfEdges:
	// - source != NULL;
	// - next != NULL;
	// - next->prev = halfEdge
	// - prev != NULL;
	// - prev->next = halfEdge
	// - twin != NULL;
	// - twin->twin = halfEdge
	// - adjacentFace != NULL;
	HalfEdge* halfEdge;
	for (unsigned int i = 0; i < halfEdges.size(); i++)
	{
		std::stringstream sst;
		sst << i;
		halfEdge = halfEdges[i];
		if (halfEdge->source == NULL)
			errors.push_back(std::string("halfEdges[" + sst.str() + "] : halfEdge->source == NULL"));
		if (halfEdge->next == NULL)
			errors.push_back("halfEdges[" + sst.str() + "] : halfEdge->next == NULL");
		else if (halfEdge->next->prev != halfEdge)
			errors.push_back("halfEdges[" + sst.str() + "] : halfEdge->next->prev != halfEdge");
		if (halfEdge->prev == NULL)
			errors.push_back("halfEdges[" + sst.str() + "] : halfEdge->prev == NULL");
		else if (halfEdge->prev->next != halfEdge)
			errors.push_back("halfEdges[" + sst.str() + "] : halfEdge->prev->next != halfEdge");
		if (halfEdge->twin == NULL)
			errors.push_back("halfEdges[" + sst.str() + "] : halfEdge->twin == NULL");
		else if (halfEdge->twin->twin != halfEdge)
			errors.push_back("halfEdges[" + sst.str() + "] : halfEdge->twin->twin != halfEdge");
		if (halfEdge->adjacentFace == NULL)
			errors.push_back("halfEdges[" + sst.str() + "] : halfEdge->adjacentFace == NULL");
	}

	// Vertices:
	// - originOf != NULL;
	// - vertex == vertex->orginOf->source
	// - closed fan
	Vertex* vertex;
	for (unsigned int i = 0; i < vertices.size(); i++)
	{
		std::stringstream sst;
		sst << i;
		vertex = vertices[i];
		if (vertex->originOf == NULL)
			errors.push_back("vertices[" + sst.str() + "] : originOf == NULL");
		else if (vertex->originOf->source != vertex)
			errors.push_back("vertices[" + sst.str() + "] : vertex != vertex->orginOf->source");
		else
		{
			HalfEdge* e = vertex->originOf;
			int k = 0;
			do
			{
				k++;
				e = e->next;
			} while (e != vertex->originOf && k < 10000);

			if (e != vertex->originOf)
				errors.push_back("vertices[" + sst.str() + "] : incorrect fan");
		}
	}

	// Faces
	// - adjacentHalfEdge != NULL
	// - Check if faces are closed + count halfEdges
	// - Total halfedges = halfedges.size()
	Face* face;
	unsigned int nbHalfEdges = 0;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		std::stringstream sst;
		sst << i;
		face = faces[i];
		if (face->adjacentHalfEdge == NULL)
			errors.push_back("faces[" + sst.str() + "] : face->adjacentHalfEdge == NULL");
		else
		{
			HalfEdge* e = face->adjacentHalfEdge;
			int k = 0;
			do
			{
				k++;
				e = e->next;
			} while (e != face->adjacentHalfEdge && k < 10000);

			if (e != face->adjacentHalfEdge)
				errors.push_back("faces[" + sst.str() + "] : face not closed");
			else
				nbHalfEdges += k;
		}
	}

	if (nbHalfEdges != halfEdges.size())
		errors.push_back("faces : nbHalfEdges != halfEdges.size()");

	return errors.size() == 0;
}

void Mesh::ComputeNormals()
{
	for (unsigned int i = 0; i < faces.size(); i++)
		faces[i]->ComputeNormal();

	for (unsigned int i = 0; i < vertices.size(); i++)
		vertices[i]->ComputeNormal();
}
