#pragma once

#include "Vertex.h"
#include "Face.h""
#include "Dependencies/glm/glm.hpp"

namespace Model
{
	class HalfEdge
	{
		public:
			Vertex* source;
			HalfEdge* next;
			HalfEdge* prev;
			HalfEdge* twin;
			Face* adjacentFace;

			HalfEdge();
			~HalfEdge();
			double GetLength();
	};
}