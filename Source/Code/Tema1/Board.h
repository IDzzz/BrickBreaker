#pragma once
#include <Core/Engine.h>

class Board {
public:
	Board()
	{
	}
	Board(float boardH, float boardW, glm::vec3 cor)
	{
		corner = cor;
		w = boardW;
		h = boardH;
	}
	// Width
	float w;
	// Height
	float h;

	// Coltul stanga jos
	glm::vec3 corner;
};