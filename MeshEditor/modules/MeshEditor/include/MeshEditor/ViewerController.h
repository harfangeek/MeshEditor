#pragma once

namespace Rendering
{
	class MeshRenderer;
}

namespace MeshEditor
{
	class ViewerController
	{
	public:
		ViewerController(Rendering::MeshRenderer* meshRenderer);
		~ViewerController();

		void Update();
		

		bool mesh, wireframe, vertices, facesNormals, verticesNormals;
		float meshColor[4], wireframeColor[4], verticesColor[4], facesNormalsColor[4], verticesNormalsColor[4];

	private:
		Rendering::MeshRenderer* meshRenderer;
		
	};
}
