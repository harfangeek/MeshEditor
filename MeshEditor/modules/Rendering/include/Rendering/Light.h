#pragma once

#include "GLM/glm.hpp"

namespace Rendering
{
	enum class LightType {
		AMBIANT = 0,
		POINT_LIGHT,
		DIRECTIONNAL,
		SPOT_LIGHT,
		SILOUHETTE
	};

	class Light
	{
	public:
		Light();
		~Light();

		void SetType(const LightType pType);
		void SetColor(const glm::vec4 &pColor);
		void SetPosition(const glm::vec3 &pPosition);
		void SetDirection(const glm::vec3 &pDirection);
		void SetAngle(float angle);

		LightType GetType();
		glm::vec4 GetColor();
		glm::vec3 GetPosition();
		glm::vec3 GetDirection();
		float GetAngle();

	private:
		LightType type;
		glm::vec4 color;
		glm::vec3 position;
		glm::vec3 direction;
		float angle;
	};
}
