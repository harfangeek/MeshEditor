#pragma once

#include <vector>
#include <string>

#include "GLM/glm.hpp"

namespace Rendering
{
	class Vertex;
	class Face;
	class HalfEdge;

	class Mesh
	{
	public:
		std::vector<Vertex*> vertices;
		std::vector<HalfEdge*> halfEdges;
		std::vector<Face*> faces;

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
