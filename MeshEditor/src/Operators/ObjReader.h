#include "Model\Mesh.h"
#include <vector>
#include "Dependencies\glm\glm.hpp"

namespace Operators
{
	class ObjReader
	{
		public:
			static bool Read(std::string fileName, std::vector<glm::vec3> &vertices, std::vector<std::vector<unsigned int>> &faces);
	};
}
