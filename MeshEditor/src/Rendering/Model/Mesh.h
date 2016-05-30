#pragma once

#include <Vector>
#include "Rendering\Model\Face.h"
#include "Rendering\Model\Vertex.h"
#include "Rendering\Model\HalfEdge.h"

namespace Rendering
{
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
}