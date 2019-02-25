#pragma once

#include <vector>
#include <string>
#include "Rendering/Model/Face.h"
#include "Rendering/Model/Vertex.h"
#include "Rendering/Model/HalfEdge.h"

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

			Mesh& operator=(Mesh&& other);
			Mesh(Mesh&& other);

			std::vector<std::string> Check(); // Check if the mesh contains errors (e.g. non closed face)
			void Normalize(); // Center the model on the (0,0,0) position and scale the model so it fits in a 1*1*1 cube
			void ComputeNormals(); // Compute faces and vertices normals

		};
	}
}