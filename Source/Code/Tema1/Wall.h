#pragma once
#include <Core/Engine.h>

class Wall {
public:
	Wall(float wallH, float wallW, glm::vec3 cor, bool type)
	{
		corner = cor;
		h = wallH;
		w = wallW;
		lateral = type;
	}

	// Perete lateral
	bool lateral;

	float h;
	float w;

	// Colt stanga jos
	glm::vec3 corner;
};