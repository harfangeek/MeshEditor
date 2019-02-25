#pragma once

#define GLM_FORCE_SILENT_WARNINGS 1
#include "GLM/glm.hpp"

namespace Rendering
{
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
}