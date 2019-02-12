#pragma once
#include <Core/Engine.h>
class Powerup {
public:
	Powerup(glm::vec3 cor, float powerupS, int t)
	{
		corner = cor;
		size = powerupS;
		type = t;
		angle = 0;
	}

	// 4 tipuri de powerups
	int type;

	// Latura patratului reprezentand powerup-ul
	float size;

	// Unghi de rotatie
	float angle;

	// Colt stanga jos
	glm::vec3 corner;

	virtual bool operator==(const Powerup& other)
	{
		if (other.corner.x == this->corner.x && other.corner.y == this->corner.y)
			return true;
		return false;
	}
};