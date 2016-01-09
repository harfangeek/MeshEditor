#pragma once

#include "Dependencies/glm/glm.hpp"

namespace Model
{
	class Vertex;
	class Face;

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

			double GetLength(); // Get edge length
	};
}