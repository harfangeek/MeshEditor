#include "Core\MeshRenderer.h"
#include "Operators\MeshConverter.h"

using namespace Core;

MeshRenderer::MeshRenderer(Model::Mesh* mesh)
{
	SetMesh(mesh);
}

MeshRenderer::~MeshRenderer()
{
}

void MeshRenderer::SetMesh(Model::Mesh* mesh)
{
	if (mesh != NULL)
	{
		this->mesh = mesh;
		Init();
	}
}

Model::Mesh* MeshRenderer::GetMesh()
{
	return mesh;
}

void MeshRenderer::Init()
{
	Update();
	glGenBuffers(3, buffers);
	
	// Vertices
	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices.front(), GL_STATIC_DRAW);

	// Faces
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, faces.size() * sizeof(GLuint), &faces.front(), GL_STATIC_DRAW);

	// Normals
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[2]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, normals.size() * sizeof(float), &normals.front(), GL_STATIC_DRAW);
}

// Must be called whenever the mesh structure has changed.
// Update vertices, faces and normals arrays
void MeshRenderer::Update()
{
	Operators::MeshConverter::HalfEdgeStructureToArray(*mesh, vertices, faces, normals);
}

// Display the model by sending the vertices, faces and normals arrays to the graphic card
void MeshRenderer::Display()
{
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[2]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
	glDrawElements(GL_TRIANGLE_FAN, faces.size(), GL_UNSIGNED_INT, 0);
}