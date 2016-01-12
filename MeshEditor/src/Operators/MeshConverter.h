#include "Model\Mesh.h"
#include <vector>
#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glew\glew.h"

namespace Operators
{
	class MeshConverter
	{
		public:
			// Generate a mesh in half edge structure from an array of vertices and an array of indices
			// @param mesh : The mesh to construct
			// @param vertices : The list of vertices positions
			// @param faces : The list of faces. Each face is represented by an array of n integer (n the number of vertex per face). 
			//				  Each integer is an index refering to the vertices array
			static void ArrayToHalfEdgeStructure(Model::Mesh &mesh, std::vector<glm::vec3> &vertices, std::vector<std::vector<unsigned int>> &faces);

			static void HalfEdgeStructureToArray(Model::Mesh &mesh, std::vector<GLfloat> &vertices, std::vector<GLuint> &faces);
	};
}
