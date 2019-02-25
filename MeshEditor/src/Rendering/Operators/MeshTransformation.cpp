#include "Rendering/Operators/MeshTransformation.h"
#include "Rendering/Model/Vertex.h"
#include "Rendering/Model/HalfEdge.h"
#include "Rendering/Model/Face.h"
#include <vector>

using namespace Rendering;
using namespace Rendering::Operators;
using namespace Rendering::Model;
using namespace std;

void MeshTransformation::Triangulate(Model::Mesh* mesh)
{
	Face* face = NULL;
	Face* newFace = NULL;
	HalfEdge* edge = NULL;
	HalfEdge *newEdge1, *newEdge2; // newEdge1 belong to the new face, newEdge2 belong to the remaining face
	unsigned int nbVertices, nbFaces;
	vector<Face*> newFaces;

	nbFaces = static_cast<unsigned int>(mesh->faces.size());

	for (unsigned int i = 0 ; i < nbFaces; i++)
	{
		face = mesh->faces[i];
		nbVertices = face->CountVertices();
		edge = face->adjacentHalfEdge;

		// Instanciate new faces, but we keep the original face as the last triangle
		
		newFaces.reserve(2);
		for (unsigned int j = 0; j * 2 < nbVertices - 3; j++)
		{
			newFace = new Face();
			newFaces.push_back(newFace);
			mesh->faces.push_back(newFace);
		}
		newFaces.push_back(face);

		// Triangulate the current face, each iteration create a new triangle
		for (unsigned int j = 0; j * 2 < nbVertices - 3; j++)
		{
			newFaces[j]->adjacentHalfEdge = edge;

			// Create new half edges
			newEdge1 = new HalfEdge();
			newEdge2 = new HalfEdge();
			mesh->halfEdges.push_back(newEdge1);
			mesh->halfEdges.push_back(newEdge2);
			
			// Initialize new half edges
			newEdge1->next = edge;
			newEdge1->prev = edge->next;
			newEdge1->twin = newEdge2;
			newEdge1->source = edge->next->next->source;
			newEdge1->adjacentFace = newFaces[j];

			newEdge2->next = edge->next->next;
			newEdge2->prev = edge->prev;
			newEdge2->twin = newEdge1;
			newEdge2->source = edge->source;
			newEdge2->adjacentFace = newFaces[j + 1];

			// Save first edge of remaining face
			edge = edge->next->next;

			// Consolidate existant edges
			newEdge1->prev->next = newEdge1;
			newEdge1->next->prev = newEdge1;
			newEdge2->prev->next = newEdge2;
			newEdge2->next->prev = newEdge2;
		}

		// Consolidate original face (now the last triangle)
		face->adjacentHalfEdge = edge;
		newFaces.clear();
	}
}

void MeshTransformation::Inflate(Model::Mesh* mesh, float value)
{
	for (auto vertex : mesh->vertices)
		vertex->position += value * vertex->normal;
}