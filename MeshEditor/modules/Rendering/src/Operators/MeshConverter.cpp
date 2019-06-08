#include "Rendering/MeshConverter.h"
#include "Rendering/Mesh.h"
#include "Rendering/Vertex.h"
#include "Rendering/HalfEdge.h"
#include "Rendering/Face.h"

#include <map>

using namespace Rendering;
using namespace std;

void MeshConverter::ArrayToHalfEdgeStructure(Mesh& mesh, const vector<glm::vec3> &vertices, const vector<vector<unsigned int>> &faces)
{
	// Create vertices
	size_t size_vertices = vertices.size();
	mesh.vertices.reserve(size_vertices);
	for (unsigned int i = 0; i < size_vertices; i++)
		mesh.vertices.emplace_back(new Vertex(vertices[i]));

	// Create faces
	size_t size_faces = faces.size();
	mesh.faces.reserve(size_faces);
	for (unsigned int i = 0; i < size_faces; i++)
		mesh.faces.emplace_back(new Face());

	Face *face;
	HalfEdge *firstEdge, *lastEdge, *prev, *curr;
	unsigned int v0, v1;
	unsigned int currIndex, nextIndex, lastIndex;	
	size_t sizeVertices;
	int i = 0;
	map<pair<unsigned int, unsigned int>, HalfEdge*> hmap; // Store if we already created the edge between two vertices
	map<pair<unsigned int, unsigned int>, HalfEdge*>::iterator halfEdgeIt;
	pair<unsigned int, unsigned int> pair;
	
	for(auto vertexIndices : faces)
	{
		face = mesh.faces[i];
		v0 = vertexIndices[0];
		v1 = vertexIndices[1];
		sizeVertices = vertexIndices.size();

		// Create the first half edge
		firstEdge = new HalfEdge();
		firstEdge->adjacentFace = face;
		firstEdge->source = mesh.vertices[v0];		

		face->adjacentHalfEdge = firstEdge; // Link the face to the first half edge
		mesh.vertices[v0]->originOf = firstEdge; // Link the first vertex to the first half edge

		// Consolidate faces. Check whether the half edge's twin has already been created, e.g. If there is an edge beetween the vertices 3 and 5, 
		// and two faces sharing this edge, we will try to create first the half edge 3 to 5, and later the half edge 5 to 3 (or vice versa)
		// The second time we have to link the two half edges by settings their twins
		pair.first = v1;
		pair.second = v0;
		halfEdgeIt = hmap.find(pair);
		if (halfEdgeIt != hmap.end())
		{
			firstEdge->twin = halfEdgeIt->second;
			halfEdgeIt->second->twin = firstEdge;
		}

		mesh.halfEdges.push_back(firstEdge);
		pair.first = v0;
		pair.second = v1;
		hmap[pair] = firstEdge;

		// Create intermediare edges
		prev = firstEdge;
		curr = NULL;
		currIndex = 0;
		lastIndex = vertexIndices[sizeVertices - 1];
		for (size_t j = 1; j < sizeVertices - 1; j++)
		{
			currIndex = vertexIndices[j];
			nextIndex = vertexIndices[j + 1];

			// New halfedge
			curr = new HalfEdge();
			curr->prev = prev;
			curr->adjacentFace = face;
			curr->source = mesh.vertices[currIndex];

			prev->next = curr; // Set the next of previous half edge
			mesh.vertices[currIndex]->originOf = curr; // Set current vertex has origin of the new half edge

			// Consolidate faces
			pair.first = nextIndex;
			pair.second = currIndex;
			halfEdgeIt = hmap.find(pair);
			if (halfEdgeIt != hmap.end())
			{
				curr->twin = halfEdgeIt->second;
				halfEdgeIt->second->twin = curr;
			}

			mesh.halfEdges.push_back(curr);
			pair.first = currIndex;
			pair.second = nextIndex;
			hmap[pair] = curr;
			prev = curr;
		}

		// Create the last edge
		lastEdge = new HalfEdge();
		lastEdge->prev = curr;
		lastEdge->next = firstEdge;
		lastEdge->adjacentFace = face;
		lastEdge->source = mesh.vertices[lastIndex];

		// Consolidate faces
		pair.first = v0;
		pair.second = lastIndex;
		halfEdgeIt = hmap.find(pair);
		if (halfEdgeIt != hmap.end())
		{
			lastEdge->twin = halfEdgeIt->second;
			halfEdgeIt->second->twin = lastEdge;
		}
		
		mesh.halfEdges.push_back(lastEdge);
		pair.first = lastIndex;
		pair.second = v0;
		hmap[pair] = lastEdge;

		firstEdge->prev = lastEdge;
		curr->next = lastEdge;
		mesh.vertices[lastIndex]->originOf = lastEdge;

		i++;
	}
	
	mesh.Normalize();
}

void MeshConverter::HalfEdgeStructureToArray(const Mesh& mesh, vector<GLfloat>& vertices, vector<GLuint>& faces, std::vector<GLfloat>& normals)
{
	// Add vertices
	int i = 0;
	vertices.reserve(mesh.vertices.size() * 3);
	normals.reserve(mesh.vertices.size() * 3);
	for (auto vertex : mesh.vertices)
	{
		vertices.push_back(vertex->position.x);
		vertices.push_back(vertex->position.y);
		vertices.push_back(vertex->position.z);
		normals.push_back(vertex->normal.x);
		normals.push_back(vertex->normal.y);
		normals.push_back(vertex->normal.z);
		vertex->index = i++;
	}

	// Add faces
	faces.reserve(mesh.faces.size() * 3);
	for (auto face : mesh.faces)
	{
		vector<Vertex*> faceVertices = face->ListVertices();
		for (auto vertex : faceVertices)
		{
			faces.push_back(vertex->index);
		}
		/*normals.push_back((*faceIt)->normal.x);
		normals.push_back((*faceIt)->normal.y);
		normals.push_back((*faceIt)->normal.z);*/
	}
}
