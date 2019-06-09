#include "Rendering/Mesh.h"
#include "Rendering/Face.h"
#include "Rendering/Vertex.h"
#include "Rendering/HalfEdge.h"

using namespace Rendering;
using namespace std;

Mesh::Mesh()
{
}

Mesh::~Mesh()
{
	Clean();
}

void Mesh::Clean()
{
	for (auto halfEdge : halfEdges)
		if (halfEdge != NULL)
			delete halfEdge;

	halfEdges.clear();

	for (auto vertex : vertices)
		if (vertex != NULL)
			delete vertex;

	vertices.clear();

	for (auto face : faces)
		if (face != NULL)
			delete face;

	faces.clear();
}

Mesh::Mesh(Mesh&& other) : vertices{move(other.vertices)},
								halfEdges{move(other.halfEdges)},
								faces{move(other.faces)},
								color{other.color}
{
}

Mesh& Mesh::operator=(Mesh&& other)
{
	Clean();
	vertices = move(other.vertices);
	halfEdges = move(other.halfEdges);
	faces = move(other.faces);
	color = other.color;

	return *this;
}

std::vector<std::string> Mesh::Check()
{	
	std::vector<std::string> errors;

	// HalfEdges:
	// - source != NULL;
	// - next != NULL;
	// - next->prev = halfEdge
	// - prev != NULL;
	// - prev->next = halfEdge
	// - twin != NULL;
	// - twin->twin = halfEdge
	// - adjacentFace != NULL;
	int i = 0;
	for (auto halfEdge : halfEdges)
	{
		if (halfEdge->source == NULL)
			errors.push_back(std::string("halfEdges[" + std::to_string(i) + "] : halfEdge->source == NULL"));
		if (halfEdge->next == NULL)
			errors.push_back("halfEdges[" + std::to_string(i) + "] : halfEdge->next == NULL");
		else if (halfEdge->next->prev != halfEdge)
			errors.push_back("halfEdges[" + std::to_string(i) + "] : halfEdge->next->prev != halfEdge");
		if (halfEdge->prev == NULL)
			errors.push_back("halfEdges[" + std::to_string(i) + "] : halfEdge->prev == NULL");
		else if (halfEdge->prev->next != halfEdge)
			errors.push_back("halfEdges[" + std::to_string(i) + "] : halfEdge->prev->next != halfEdge");
		if (halfEdge->twin == NULL)
			errors.push_back("halfEdges[" + std::to_string(i) + "] : halfEdge->twin == NULL");
		else if (halfEdge->twin->twin != halfEdge)
			errors.push_back("halfEdges[" + std::to_string(i) + "] : halfEdge->twin->twin != halfEdge");
		if (halfEdge->adjacentFace == NULL)
			errors.push_back("halfEdges[" + std::to_string(i) + "] : halfEdge->adjacentFace == NULL");

		i++;
	}

	// Vertices:
	// - originOf != NULL;
	// - vertex == vertex->orginOf->source
	// - closed fan
	HalfEdge* e;
	i = 0;
	for (auto vertex : vertices)
	{		
		if (vertex->originOf == NULL)
			errors.push_back("vertices[" + std::to_string(i) + "] : originOf == NULL");
		else if (vertex->originOf->source != vertex)
			errors.push_back("vertices[" + std::to_string(i) + "] : vertex != vertex->orginOf->source");
		else
		{
			e = vertex->originOf;
			int k = 0;
			do
			{
				k++;
				e = e->next;
			} while (e != vertex->originOf && k < 10000); // Avoid infinite loop

			if (e != vertex->originOf)
				errors.push_back("vertices[" + std::to_string(i) + "] : incorrect fan");
		}

		i++;
	}

	// Faces
	// - adjacentHalfEdge != NULL
	// - Check if faces are closed + count halfEdges
	// - Total halfedges = halfedges.size()
	i = 0;
	unsigned int nbHalfEdges = 0;
	int k;
	for (auto face : faces)
	{
		if (face->adjacentHalfEdge == NULL)
			errors.push_back("faces[" + std::to_string(i) + "] : face->adjacentHalfEdge == NULL");
		else
		{
			e = face->adjacentHalfEdge;
			k = 0;
			do
			{
				k++;
				e = e->next;
			} while (e != face->adjacentHalfEdge && k < 10000);  // Avoid infinite loop

			if (e != face->adjacentHalfEdge)
				errors.push_back("faces[" + std::to_string(i) + "] : face not closed");
			else
				nbHalfEdges += k;
		}

		i++;
	}

	if (nbHalfEdges != halfEdges.size())
		errors.push_back("faces : nbHalfEdges != halfEdges.size()");

	return errors;
}

void Mesh::Normalize()
{
	if (vertices.size() > 0)
	{
		Vertex *v = vertices[0];
		Vertex *vxmin = v, *vymin = v, *vzmin = v, *vxmax = v, *vymax = v, *vzmax = v;

		// Find the minimum and maximum for all x,y,z components between all the vertices positions
		for (auto v : vertices)
		{
			if (v->position.x < vxmin->position.x)
				vxmin = v;
			if (v->position.x > vxmax->position.x)
				vxmax = v;

			if (v->position.y < vymin->position.y)
				vymin = v;
			if (v->position.y > vymax->position.y)
				vymax = v;

			if (v->position.z < vzmin->position.z)
				vzmin = v;
			if (v->position.z > vzmax->position.z)
				vzmax = v;
		}

		float xmin = vxmin->position.x, xmax = vxmax->position.x,
			ymin = vymin->position.y, ymax = vymax->position.y,
			zmin = vzmin->position.z, zmax = vzmax->position.z;

		float distx = xmax - xmin, disty = ymax - ymin, distz = zmax - zmin;
		float diffx = (xmax + xmin) / 2.0f, diffy = (ymax + ymin) / 2.0f, diffz = (zmax + zmin) / 2.0f;

		// The scale factor corresponds to the greatest distance between the three maximums and minimums
		float scale = distx > disty ? distx : disty > distz ? disty : distz;

		for (auto v : vertices)
		{
			// Center the model on the (0,0,0) position
			v->position.x -= diffx;
			v->position.y -= diffy;
			v->position.z -= diffz;

			// Scale down the model by diving all positions by the scale factor
			v->position /= scale;
		}
	}
}

void Mesh::ComputeNormals()
{
	for (auto face : faces)
		face->ComputeNormal();

	for (auto vertex : vertices)
		vertex->ComputeNormal();
}
