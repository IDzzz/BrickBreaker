#pragma once

#include <Component/SimpleScene.h>
#include "Brick.h"
#include "Wall.h"
#include "Board.h"
#include "Ball.h"
#include "Powerup.h"
#include <list> 
#include <string>
#include <Core/Engine.h>

class Tema1 : public SimpleScene
{
public:
	Tema1();
	~Tema1();

	void Init() override;

private:
	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;

	void OnInputUpdate(float deltaTime, int mods) override;
	void OnKeyPress(int key, int mods) override;
	void OnKeyRelease(int key, int mods) override;
	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
	void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
	void OnWindowResize(int width, int height) override;

	void interpretPower();
	void resetPower();
	void collide();
	void reset();

	void initMeshes();
	void initGame();

protected:
	glm::mat3 modelMatrix;

	// Lista de caramizi
	std::list<Brick> bricks;
	// Lista peretilor
	std::list<Wall> walls;
	// Lista powerup-urilor ce apar in scena
	std::list<Powerup> powerups;
	// Platforma
	Board board;
	// Bila
	Ball ball;

	// Numar vieti jucator
	int lifes;
	
	// Jucatorul a obtinut o noua putere
	bool newPower;
	// Tipul puterii
	int powerType;
	// Timpul ramas din putere
	float powerTime;

	// Viteza initiala a bilei
	float initialSpeed = 600;

	// Latimea platformei
	float boardWidth;
};

