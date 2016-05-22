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
			glm::vec4 color;

			Mesh();
			~Mesh();
			void Clean();

			bool Check(std::vector<std::string>& errors); // Check if the mesh contains errors (e.g. non closed face)
			void Mesh::Normalize(); // TODO
			void ComputeNormals(); // Compute faces and vertices normals

	};
}