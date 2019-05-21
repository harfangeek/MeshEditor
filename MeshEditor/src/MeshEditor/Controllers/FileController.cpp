#include "MeshEditor/Controllers/FileController.h"
#include "Rendering/Model/Mesh.h"
#include "Rendering/Operators/Objreader.h"
#include "Rendering/Operators/MeshTransformation.h"
#include "Rendering/Core/MeshRenderer.h"

using namespace MeshEditor::Controllers;
using namespace Rendering::Core;
using namespace Rendering::Model;
using namespace Rendering::Operators;

FileController::FileController(Rendering::Core::MeshRenderer* meshRenderer) : meshRenderer(meshRenderer)
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
	auto mesh = Rendering::Operators::ObjReader::LoadMesh(path);
	Rendering::Operators::MeshTransformation::Triangulate(mesh);
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
	Rendering::Operators::ObjReader::SaveMesh(*(meshRenderer->GetMesh()), path);
	return "";
}

