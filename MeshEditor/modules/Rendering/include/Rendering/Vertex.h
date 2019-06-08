#pragma once

#include <vector>
#include "GLM/glm.hpp"

namespace Rendering
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
		Vertex(const glm::vec3& pos);
		~Vertex();

		std::vector<Face*> ListFaces(); // List faces around the vertex
		unsigned int CountFaces(); // Return the number of faces around the vertex
		void ComputeNormal(); // Compute the normal of the vertex (update normal member)
	};
}
