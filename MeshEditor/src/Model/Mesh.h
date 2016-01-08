#pragma once

#include <Vector>
#include "Face.h"
#include "Vertex.h"
#include "HalfEdge.h"

namespace Model
{
	class Mesh
	{
		public:
			std::vector<Vertex*> vertices;
			std::vector<HalfEdge*> halfEdges;
			std::vector<Face*> faces;

			Mesh();
			~Mesh();
	};
}