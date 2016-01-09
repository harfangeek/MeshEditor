#pragma once

#include <Vector>
#include "Model\Face.h"
#include "Model\Vertex.h"
#include "Model\HalfEdge.h"

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

			bool Check(std::vector<std::string>& errors); // Check if the mesh contains errors (e.g. non closed face)
			void computeNormals(); // Compute faces and vertices normals
	};
}