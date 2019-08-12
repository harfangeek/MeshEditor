#include "Rendering/SceneRenderer.h"
#include "Rendering/MeshRenderer.h"
#include "Rendering/Camera.h"
#include "Rendering/Light.h"
#include "Rendering/ShaderLoader.h"

#include "GLM/glm.hpp"
#include "GLM/gtc/matrix_transform.hpp"

using namespace Rendering;
using namespace glm;

SceneRenderer::SceneRenderer(Camera* camera, Light* light) : camera(camera),
															 light(light)
{
	InitShader();
}

SceneRenderer::~SceneRenderer()
{
	glDeleteProgram(program);
}

void SceneRenderer::InitShader()
{
	glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);

	// Create shaders
	program = ShaderLoader::CreateProgram("resources/shaders/vertexShader.glsl", "resources/shaders/fragmentShader.glsl");
	InitCamera(); 
	InitLight();
}

void SceneRenderer::InitCamera()
{
	projectionMatrixLoc = glGetUniformLocation(program, "projection_matrix");
	viewMatrixLoc = glGetUniformLocation(program, "view_matrix");
}

void SceneRenderer::InitLight()
{
	lightTypeLoc = glGetUniformLocation(program, "light_type");
	lightColorLoc = glGetUniformLocation(program, "light_color");
	lightPositionLoc = glGetUniformLocation(program, "light_position");
	lightDirectionLoc = glGetUniformLocation(program, "light_direction");
	lightAngleLoc = glGetUniformLocation(program, "light_angle");
}

void SceneRenderer::AddMeshRenderer(MeshRenderer* renderer)
{
	meshRenderers.push_back(renderer);
	renderer->Init(program);
}

void SceneRenderer::SetCamera(Camera* camera)
{
	this->camera = camera;
}

void SceneRenderer::SetLight(Light* light)
{
	this->light = light;
}

const std::vector<MeshRenderer*>& SceneRenderer::GetMeshRenderers()
{
	return meshRenderers;
}

Camera* SceneRenderer::GetCamera()
{
	return camera;
}

Light* SceneRenderer::GetLight()
{
	return light;
}

void SceneRenderer::Display(Camera* pCamera)
{
	Camera* currentCamera = pCamera;
	if (!currentCamera)
		currentCamera = camera;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, currentCamera->GetViewportWidth(), currentCamera->GetViewportHeight());

	glUseProgram(program);
	SendCameraData(currentCamera);
	SendLightData();

	for (auto renderer : meshRenderers)
		renderer->Display();
}

void SceneRenderer::SendCameraData(Camera* pCamera)
{
	glm::mat4 projection_matrix = glm::perspective(pCamera->GetFovy(), (float)pCamera->GetViewportWidth() / (float)pCamera->GetViewportHeight(), pCamera->GetZNear(), pCamera->GetZFar());
	glUniformMatrix4fv(projectionMatrixLoc, 1, GL_FALSE, &projection_matrix[0][0]);

	glm::mat4 view_matrix = glm::lookAt(pCamera->GetCameraEye(), pCamera->GetCameraEye() + pCamera->GetCameraForward(), pCamera->GetCameraUp());
	glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE, &view_matrix[0][0]);
}

void SceneRenderer::SendLightData()
{
	glm::vec4 lightColor = light->GetColor();
	glm::vec3 lightPosition = light->GetPosition();
	glm::vec3 lightDirection = light->GetDirection();
	float lightAngle = light->GetAngle();

	glUniform4f(lightColorLoc, lightColor.r, lightColor.g, lightColor.b, lightColor.a);
	glUniform3f(lightPositionLoc, lightPosition.x, lightPosition.y, lightPosition.z);
	glUniform3f(lightDirectionLoc, lightDirection.x, lightDirection.y, lightDirection.z);
	glUniform1f(lightAngleLoc, lightAngle);
}
