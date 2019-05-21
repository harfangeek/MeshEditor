#pragma once

#include <vector>
#include "GLM/glm.hpp"

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
			std::vector<HalfEdge*> ListHalfEdges(); // List the halfedges of the face
			unsigned int CountHalfEdges(); // Return the number of halfedges of the face
			std::vector<Vertex*> ListVertices(); // List the vertices of the face
			unsigned int CountVertices(); // Return the number of vertices of the face
			std::vector<Face*> ListNeighbourFaces(); // List the faces around the face
			unsigned int CountNeighbourFaces(); // Return the number of faces around the face
		};
	}
}