#pragma once

#include "Dependencies\glm\glm.hpp"

namespace Model
{
	class Vertex
	{
		public:
			glm::vec3 position;
			glm::vec3 normal;
			HalfEdge* originOf;

			Vertex();
			~Vertex();

			void ComputeNormal();
	};
}