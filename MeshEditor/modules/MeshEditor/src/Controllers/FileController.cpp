#include "MeshEditor/FileController.h"
#include "Rendering/Mesh.h"
#include "Rendering/ObjReader.h"
#include "Rendering/MeshTransformation.h"
#include "Rendering/MeshRenderer.h"

#include <cstring>

using namespace MeshEditor;

FileController::FileController(Rendering::MeshRenderer* meshRenderer) : meshRenderer(meshRenderer)
{
	memset(path, 0, pathSize);
}

FileController::~FileController()
{

}

void FileController::SetPath(std::string newPath)
{
#ifdef _MSC_VER
	strncpy_s(path, 2048, newPath.c_str(), 2047);
#else
	std::strncpy(path, newPath.c_str(), 2047);
#endif
}

char* FileController::GetPath()
{
	return path;
}

std::string FileController::Load()
{
	auto mesh = Rendering::ObjReader::LoadMesh(path);
	if (mesh)
	{
		Rendering::MeshTransformation::Triangulate(mesh);
		mesh->ComputeNormals();
		mesh->color = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);

		auto oldMesh = meshRenderer->GetMesh();
		meshRenderer->SetMesh(mesh);
		if (oldMesh)
			delete oldMesh;
	}

	return "";
}

std::string FileController::Save()
{
	if(meshRenderer->GetMesh())
		Rendering::ObjReader::SaveMesh(*(meshRenderer->GetMesh()), path);

	return "";
}

