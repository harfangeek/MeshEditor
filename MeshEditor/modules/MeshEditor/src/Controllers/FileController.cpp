#include "MeshEditor/FileController.h"
#include "Rendering/Mesh.h"
#include "Rendering/ObjReader.h"
#include "Rendering/MeshTransformation.h"
#include "Rendering/MeshRenderer.h"

using namespace MeshEditor;

FileController::FileController(Rendering::MeshRenderer* meshRenderer) : meshRenderer(meshRenderer)
{
	path = "Models/hand.obj";
}

FileController::~FileController()
{

}

void FileController::SetPath(std::string path)
{
	this->path = path;
}

std::string FileController::GetPath()
{
	return path;
}

std::string FileController::Load()
{
	auto mesh = Rendering::ObjReader::LoadMesh(path);
	Rendering::MeshTransformation::Triangulate(mesh);
	mesh->ComputeNormals();
	mesh->color = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);

	auto oldMesh = meshRenderer->GetMesh();
	meshRenderer->SetMesh(mesh);
	if(oldMesh)
		delete oldMesh;

	return "";
}

std::string FileController::Save()
{
	Rendering::ObjReader::SaveMesh(*(meshRenderer->GetMesh()), path);
	return "";
}

