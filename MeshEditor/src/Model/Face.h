#pragma once

#include "HalfEdge.h"
#include "Dependencies\glm\glm.hpp"

namespace Model
{
	class Face
	{
		public:
			HalfEdge* adjacentHalfEdge;
			glm::vec3 normal;

			Face();
			~Face();

			void ComputeNormal();
			int countHalfEdges();
	};
}