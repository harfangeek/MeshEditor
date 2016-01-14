#pragma once

#include "Model\Mesh.h"
#include "Dependencies\glew\glew.h"
#include <vector>
#include "Dependencies\glew\glew.h"

namespace Core
{
	class MeshRenderer
	{
		private:
			Model::Mesh* mesh;
			std::vector<GLfloat> vertices;
			std::vector<GLuint> faces;
			std::vector<GLfloat> normals;
			GLuint buffers[3];
		
			void Init();
		public:	
			MeshRenderer(Model::Mesh* mesh = NULL);
			~MeshRenderer();

			void SetMesh(Model::Mesh* mesh);
			Model::Mesh* GetMesh();
			
			// Must be called whenever the mesh structure has changed.
			// Update vertices, faces and normals arrays
			void Update(); 

			// Display the model by sending the vertices, faces and normals arrays to the graphic card
			void Display();
	};
}
