#include "Rendering/Light.h"

//#include "GLM/glm.hpp"

using namespace Rendering;
//using namespace glm;

Light::Light() : type(LightType::AMBIANT),
				color(1.0f, 1.0f, 1.0f, 1.0f),
				position(0.0f, 0.0f, 4.0f),
				direction(0.0f, -1.0f, 0.0f),
				angle(30.0f)
{

}

Light::~Light()
{

}

void Light::SetType(LightType pType)
{
	type = pType;
}

void Light::SetColor(const glm::vec4 &pColor)
{
	color = pColor;
}

void Light::SetPosition(const glm::vec3 &pPosition)
{
	position = pPosition;
}

void Light::SetDirection(const glm::vec3 &pDirection)
{
	direction = pDirection;
}

void Light::SetAngle(float pAngle)
{
	angle = pAngle;
}

LightType Light::GetType()
{
	return type;
}

glm::vec4 Light::GetColor()
{
	return color;
}

glm::vec3 Light::GetPosition()
{
	return position;
}

glm::vec3 Light::GetDirection()
{
	return direction;
}

float Light::GetAngle()
{
	return angle;
}
