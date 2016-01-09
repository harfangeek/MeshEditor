#include "Model\Mesh.h"
#include <vector>
#include "Dependencies\glm\glm.hpp"

namespace Operators
{
	class MeshGenerator
	{
		public:
			static void Generate(Model::Mesh &mesh, std::vector<glm::vec3> &vertices, std::vector<std::vector<unsigned int>> &faces);
	};
}
