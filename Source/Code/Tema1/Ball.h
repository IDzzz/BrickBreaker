#pragma once
#include <Core/Engine.h>
#include <algorithm>
#include "Powerup.h"
class Ball {
public:
	Ball()
	{
	}
	Ball(float radius, glm::vec3 cor)
	{
		center = cor;
		r = radius;
	}

	// Verificarea coliziunilor intre bila si un dreptunghi cu height si width
	bool checkCollision(glm::vec3 pos, float height, float width)
	{
		float aux1 = fabs(center.x - (pos.x + width/2));
		float aux2 = fabs(center.y - (pos.y + height/2));
		// Daca distanta intre centrul bilei si caramida este mai mare decat
		// limite, nu se loveste
		if (aux1 > width / 2 + r || aux2 > height / 2 + r)
			return false;
		// Mai mica sau egala, se ciocneste
		if (aux1 <= width / 2 + r || aux2 <= height / 2 + r)
			return true;
		// Cazul in care cercul intersecteaza coltul
		if((aux1 - pos.x) * (aux1 - pos.x) + (aux2 - pos.y) * (aux2 - pos.y) <= r * r)
			return true;
		return false;
	}

	// Vector pentru pozitia centrului
	glm::vec3 center;
	// Viteza de miscare
	float speed;
	// Raza
	float r;
	// Variabila ce determina daca se afla in miscare
	bool inMovement;

	// Velocitatea pe OX si OY
	float tx;
	float ty;
};