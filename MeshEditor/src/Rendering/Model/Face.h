#pragma once

#include <vector>
#include "Dependencies\glm\glm.hpp"

namespace Rendering
{
	namespace Model
	{
		class HalfEdge;
		class Vertex;

		class Face
		{
		public:
			HalfEdge* adjacentHalfEdge;
			glm::vec3 normal;

			Face();
			~Face();

			void ComputeNormal(); // Compute the face's normal (update normal member)
			void ListHalfEdges(std::vector<HalfEdge*> &halfEdges); // List the halfedges of the face
			int CountHalfEdges(); // Return the number of halfedges of the face
			void ListVertices(std::vector<Vertex*> &vertices); // List the vertices of the face
			int CountVertices(); // Return the number of vertices of the face
			void ListNeighbourFaces(std::vector<Face*> &faces); // List the faces around the face
			int CountNeighbourFaces(); // Return the number of faces around the face
		};
	}
}