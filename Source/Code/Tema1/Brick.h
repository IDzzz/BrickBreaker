#pragma once
class Brick {
public:
	Brick(glm::vec3 cor, float brickH, float brickW, bool twolifes)
	{
		corner = cor;
		h = brickH;
		w = brickW;
		if (twolifes == true)
		{
			lifes = 2;
		}
		else 
		{
			lifes = 1;
		}
	}

	// Numar vieti
	int lifes;

	float h;
	float w;

	// Timp de stergere(micsorare)
	// Daca este mai mare de 0.5, stergere completa
	float deleteTime = 0;

	// Colt stanga jos
	glm::vec3 corner;

	// Supraincarcare de operator(necesar pentru remove/find)
	virtual bool operator==(const Brick& other)
	{
		if (other.corner.x == this->corner.x && other.corner.y == this->corner.y)
			return true;
		return false;
	}
};