#pragma once

#include <vector>
#include "Dependencies\glm\glm.hpp"

namespace Rendering
{
	namespace Model
	{
		class HalfEdge;
		class Face;

		class Vertex
		{
		public:
			glm::vec3 position;
			glm::vec3 normal;
			HalfEdge* originOf;
			unsigned int index;

			Vertex();
			Vertex(glm::vec3 pos);
			~Vertex();

			void ListFaces(std::vector<Face*> &faces); // List faces around the vertex
			int CountFaces(); // Return the number of faces around the vertex
			void ComputeNormal(); // Compute the normal of the vertex (update normal member)
		};
	}
}