#include "Tema1.h"
#include "Brick.h"
#include "Powerup.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <Core/Engine.h>
#include "Transform2D.h"
#include "Object2D.h"
#include <gl\gl.h>


#define PI 3.14159265
#define PowerupSide 20
#define PowerupSpeed 200

#define GGwidth 100
#define GGheight 100

using namespace std;

Tema1::Tema1()
{
}

Tema1::~Tema1()
{
}

void Tema1::Init()
{
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);
	
	initGame();

	initMeshes();
}

// Initializare joc
void Tema1::initGame()
{
	glm::ivec2 resolution = window->GetResolution();
	glm::vec3 corner = glm::vec3(0, 0, 0);

	// Curatare liste(apelez aceeasi functie si la moarte)
	bricks.clear();
	walls.clear();
	
	// Initializare valori pentru completarea informatiilor despre walls, bricks, board, wall
	powerTime = 0;
	newPower = false;
	float radius = 15;
	boardWidth = window->GetResolution().x / 8;
	float boardW = window->GetResolution().x / 8;
	float boardH = window->GetResolution().y / 70;

	float latWW = window->GetResolution().x / 60;
	float latWH = window->GetResolution().y;

	float longWW = window->GetResolution().x;
	float longWH = latWW;

	float moveX = resolution.x / 2 - boardW / 2;

	float brickH = window->GetResolution().y / 18;
	float brickW = window->GetResolution().x / 15;

	// Bricks initialize
	float auxH = window->GetResolution().y * 13 / 14;
	for (int i = 0; i < 5; i++)
	{
		auxH -= window->GetResolution().y / 14;
		float auxW = window->GetResolution().x * 2 / 14;
		for (int j = 0; j < 10; j++)
		{
			// Probabilitate de 20% sa aiba 2 vieti
			int prob20 = rand() % 5;
			bool twolifes = false;
			if (prob20 == 1) {
				twolifes = true;
			}
			// Adaugare caramida la lista
			Brick brk = Brick::Brick(glm::vec3(auxW, auxH, 0), brickH, brickW, twolifes);
			bricks.push_back(brk);
			auxW += window->GetResolution().x / 14;
		}
	}

	// Walls initialize
	walls.push_back(Wall(latWH, latWW, glm::vec3(0, window->GetResolution().y / 15, 0), true));
	walls.push_back(Wall(longWH, longWW, glm::vec3(0, window->GetResolution().y - longWH, 0), false));
	walls.push_back(Wall(latWH, latWW, glm::vec3(window->GetResolution().x - latWW, window->GetResolution().y / 15, 0), true));

	// Board
	board = Board(boardH, boardW, glm::vec3(moveX, 0, 0));

	// Ball
	ball = Ball(radius, glm::vec3(moveX, 0, 0));
	ball.center.x = moveX + boardW / 2;
	ball.center.y = boardH + radius + 5;
	ball.inMovement = false;
	ball.ty = initialSpeed;
	ball.speed = initialSpeed;
	ball.tx = 0;

	// It's alive
	lifes = 3;
	powerups.clear();
}

// Initializare meshe
void Tema1::initMeshes()
{
	glm::ivec2 resolution = window->GetResolution();
	glm::vec3 corner = glm::vec3(0, 0, 0);
	float radius = 15;

	float boardW = window->GetResolution().x / 8;
	float boardH = window->GetResolution().y / 70;

	float latWW = window->GetResolution().x / 60;
	float latWH = window->GetResolution().y * 14 / 15;

	float longWW = window->GetResolution().x;
	float longWH = latWW;

	float moveX = resolution.x / 2 - boardW / 2;

	float brickH = window->GetResolution().y / 18;
	float brickW = window->GetResolution().x / 15;

	// Meshes
	// Cele 3 tipuri de platforme
	Mesh* board = Object2D::CreateMyRectangle("board", corner, boardH, boardW, glm::vec3(0, 1, 0), true);
	Mesh* boardSmall = Object2D::CreateMyRectangle("boardSmall", corner, boardH, boardW - boardW / 4, glm::vec3(0, 0.5f, 1), true);
	Mesh* boardLarge = Object2D::CreateMyRectangle("boardLarge", corner, boardH, boardW + boardW / 4, glm::vec3(1, 1, 0), true);
	
	// Peretii
	Mesh* latW = Object2D::CreateMyRectangle("latW", corner, latWH, latWW, glm::vec3(1, 0, 0), true);
	Mesh* longW = Object2D::CreateMyRectangle("longW", corner, longWH, longWW, glm::vec3(1, 0, 0), true);
	
	// Caramizile
	Mesh* brick1 = Object2D::CreateMyRectangle("brick1", corner, brickH, brickW, glm::vec3(1, 0.75f, 0.79f), true);
	Mesh* brick2 = Object2D::CreateMyRectangle("brick2", corner, brickH, brickW, glm::vec3(1, 0, 0), true);
	
	// Powerups
	Mesh* powerup0 = Object2D::CreateMyRectangle("powerup0", corner, PowerupSide, PowerupSide, glm::vec3(1, 0.5f, 0), true);
	Mesh* powerup1 = Object2D::CreateMyRectangle("powerup1", corner, PowerupSide, PowerupSide, glm::vec3(1, 1, 0), true);
	Mesh* powerup2 = Object2D::CreateMyRectangle("powerup2", corner, PowerupSide, PowerupSide, glm::vec3(0, 0.5f, 1), true);
	Mesh* powerup3 = Object2D::CreateMyRectangle("powerup3", corner, PowerupSide, PowerupSide, glm::vec3(0, 1, 1), true);
	
	// Ball
	Mesh* ball = Object2D::CreateMyCircle("ball", radius, glm::vec3(1, 0.5f, 0));
	
	// Vieti
	Mesh* normalLife = Object2D::CreateMyCircle("normalLife", radius * 3 / 4, glm::vec3(1, 1, 1));
	Mesh* extraLife = Object2D::CreateMyCircle("extraLife", radius * 3 / 4, glm::vec3(0, 1, 0));
	
	// Litera G
	Mesh* g = Object2D::CreateGG("g", glm::vec3(window->GetResolution().x / 2 - GGwidth - 20, window->GetResolution().y / 2 - GGheight / 2, 0), GGwidth, GGheight, glm::vec3(0, 1, 0));

	AddMeshToList(board);
	AddMeshToList(boardSmall);
	AddMeshToList(boardLarge);
	AddMeshToList(latW);
	AddMeshToList(longW);
	AddMeshToList(brick1);
	AddMeshToList(brick2);
	AddMeshToList(ball);
	AddMeshToList(powerup0);
	AddMeshToList(powerup1);
	AddMeshToList(powerup2);
	AddMeshToList(powerup3);
	AddMeshToList(normalLife);
	AddMeshToList(extraLife);
	AddMeshToList(g);
}

void Tema1::FrameStart()
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glm::ivec2 resolution = window->GetResolution();
	glViewport(0, 0, resolution.x, resolution.y);
}

// Verificare coliziunii si schimbarea directilor
void Tema1::collide() 
{
	// Fiecare caramida din lista
	for (auto &brick : bricks)
	{
		if (brick.lifes > 0)
		{
			if (ball.checkCollision(brick.corner, brick.h, brick.w))
			{
				// Exista 2 cazuri
				// Loveste din partile laterale, sau de jos/sus
				if (ball.center.x <= brick.corner.x || ball.center.x >= brick.corner.x + brick.w)
				{
					ball.tx = -ball.tx;
				}
				if (ball.center.y <= brick.corner.y || ball.center.y >= brick.corner.y + brick.h)
				{
					ball.ty = -ball.ty;
				}
				// Se decrementeaza viata caramizii
				brick.lifes--;
				if(brick.lifes <= 0)
				{
					// Daca a fost sparta probabilitate de 50% sa pice powerup
					int type = rand() % 7;
					if (type <= 3)
					{
						Powerup newp = Powerup(glm::vec3(brick.corner.x + (brick.w - PowerupSide) / 2, brick.corner.y + (brick.h - PowerupSide) / 2, 0), PowerupSide, type);
						powerups.push_back(newp);
					}
				}
			}
		}
	}

	// Coliziunea cu peretii
	for (auto wall : walls) 
	{
		if (ball.checkCollision(wall.corner, wall.h, wall.w))
		{
			if (ball.center.x < wall.corner.x || ball.center.x > wall.corner.x + wall.w)
			{
				ball.tx = -ball.tx;
			}
			if (ball.center.y < wall.corner.y || ball.center.y > wall.corner.y + wall.h)
			{
				ball.ty = -ball.ty;
			}
		}
	}

	// Cu platforma
	if (ball.checkCollision(board.corner, board.h, board.w))
	{
		// Obtin unghiul
		float meh = (ball.center.x - (board.corner.x + board.w / 2)) / (board.w / 2);
		float angle = acos(meh);
		
		// Schimb velocitatile
		ball.tx = cos(angle) * ball.speed;
		ball.ty = sin(angle) * ball.speed;
	}
}

// Cand s-a pierdut bila
void Tema1::reset()
{
	lifes--;
	resetPower();
	if (lifes == 0)
	{
		// Resetare completa joc
		initGame();
	}
	else
	{
		// Continuare joc cu acelasi numar de caramizi
		// dar cu vieti mai putine
		float radius = 15;
		glm::ivec2 resolution = window->GetResolution();

		float boardW = window->GetResolution().x / 8;
		float boardH = window->GetResolution().y / 70;

		// Board
		float moveX = resolution.x / 2 - boardW / 2;
		board = Board(boardH, boardW, glm::vec3(moveX, 0, 0));

		
		// Ball
		ball = Ball(radius, glm::vec3(moveX, 0, 0));
		ball.center.x = moveX + boardW / 2;
		ball.center.y = boardH + radius + 5;
		ball.inMovement = false;
		ball.ty = initialSpeed;
		ball.speed = initialSpeed;
		ball.tx = 0;
	}
	// Curatare powerups
	powerups.clear();
}

void Tema1::Update(float deltaTimeSeconds)
{
	// Lifes
	int coordY = window->GetResolution().y * 24 / 25;
	int coordX = window->GetResolution().x / 20;
	for (int i = 1; i <= lifes; i++)
	{
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(coordX + (i - 1) * 3 * ball.r, coordY);
		// A patra viata este suplimentara(nu se poate trece de 4 vieti)
		if (i < 4)
		{
			RenderMesh2D(meshes["normalLife"], shaders["VertexColor"], modelMatrix);
		}
		else
		{
			RenderMesh2D(meshes["extraLife"], shaders["VertexColor"], modelMatrix);
		}
	}

	// Ball
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(ball.center.x, ball.center.y);
	RenderMesh2D(meshes["ball"], shaders["VertexColor"], modelMatrix);
	if (ball.inMovement == true)
	{
		// Coliziunile
		collide();
		// Avansarea bilei
		ball.center.y += deltaTimeSeconds * ball.ty;
		ball.center.x += deltaTimeSeconds * ball.tx;
	}

	// Daca s-a pierdut bila => reset
	if (ball.center.y <= 0 || ball.center.x != ball.center.x || ball.center.y != ball.center.y)
	{
		reset();
	}

	// Board
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(board.corner.x, 0);
	if (board.w == boardWidth)
	{
		RenderMesh2D(meshes["board"], shaders["VertexColor"], modelMatrix);
	}
	else if (board.w > boardWidth)
	{
		RenderMesh2D(meshes["boardLarge"], shaders["VertexColor"], modelMatrix);

	}
	else
	{
		RenderMesh2D(meshes["boardSmall"], shaders["VertexColor"], modelMatrix);
	}

	
	// Walls
	for (const auto wall : walls) {
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(wall.corner.x, wall.corner.y);
		if (wall.lateral == true)
		{
			RenderMesh2D(meshes["latW"], shaders["VertexColor"], modelMatrix);
		}
		else
		{
			RenderMesh2D(meshes["longW"], shaders["VertexColor"], modelMatrix);
		}
	}
	
	// Bricks
	// Nu mai sunt caramizi? Final de joc + GG
	if (bricks.empty()) {
		ball.tx = 0;
		ball.ty = 0;
		modelMatrix = glm::mat3(1);
		RenderMesh2D(meshes["g"], shaders["VertexColor"], modelMatrix);
		modelMatrix *= Transform2D::Translate(GGwidth + 20, 0);
		RenderMesh2D(meshes["g"], shaders["VertexColor"], modelMatrix);
		return;
	}
	// Lista de sters caramizi
	std::list<Brick> toDelete;
	for(auto &brick : bricks)
	{
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(brick.corner.x, brick.corner.y);
		if (brick.lifes == 2)
		{
			RenderMesh2D(meshes["brick2"], shaders["VertexColor"], modelMatrix);
		}
		if (brick.lifes == 1)
		{
			RenderMesh2D(meshes["brick1"], shaders["VertexColor"], modelMatrix);
		}
		if (brick.lifes <= 0 )
		{
			brick.deleteTime += deltaTimeSeconds;
			// Daca au trecut 0.3 secunde, le sterg
			if (brick.deleteTime >= 0.3)
			{
				toDelete.push_back(brick);
			}
			// Efectul de scalare cu 1 - deleteTime
			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform2D::Translate(brick.corner.x + brick.w / 2, brick.corner.y + brick.h / 2);
			modelMatrix *= Transform2D::Scale((1 - brick.deleteTime)/3, (1 - brick.deleteTime)/3);
			modelMatrix *= Transform2D::Translate(- brick.w / 2, - brick.h / 2);
			RenderMesh2D(meshes["brick1"], shaders["VertexColor"], modelMatrix);
		}
	}

	for (auto brick : toDelete) {
		bricks.remove(brick);
	}

	// Powerups
	// Decrementarea timpului
	if (powerType > 0)
		powerTime -= deltaTimeSeconds;

	std::list<Powerup> toDeletePowerups;
	for (auto& powerup : powerups)
	{
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(powerup.corner.x + powerup.size / 2, powerup.corner.y + powerup.size / 2);
		modelMatrix *= Transform2D::Rotate(powerup.angle);
		modelMatrix *= Transform2D::Translate(-powerup.size / 2, -powerup.size / 2);
		if (powerup.type == 0) {
			RenderMesh2D(meshes["powerup0"], shaders["VertexColor"], modelMatrix);
		}
		if (powerup.type == 1) {
			RenderMesh2D(meshes["powerup1"], shaders["VertexColor"], modelMatrix);

		}
		if (powerup.type == 2) {
			RenderMesh2D(meshes["powerup2"], shaders["VertexColor"], modelMatrix);
		}
		if (powerup.type == 3) {
			RenderMesh2D(meshes["powerup3"], shaders["VertexColor"], modelMatrix);
		}
		// Coborarea power-upului
		powerup.corner.y -= PowerupSpeed * deltaTimeSeconds;
		// Rotatia
		powerup.angle += 5 * deltaTimeSeconds;
		if (powerup.corner.y < board.h)
		{
			toDeletePowerups.push_back(powerup);
			// Daca a fost prins
			if (powerup.corner.x > board.corner.x && powerup.corner.x < board.corner.x + board.w)
			{
				// Activare putere noua
				newPower = true;
				powerType = powerup.type;
				powerTime = 5;
			}
		}
	}

	for (auto& power: toDeletePowerups)
	{
		powerups.remove(power);
	}

	// Putere noua => interpretare
	if (newPower == true)
	{
		interpretPower();
		newPower = false;
	}
	else
	{
		// Daca a trecut timpul, eliminare efectele puterii anterioare
		if(powerTime < 0)
		{
			resetPower();
		}
	}
}

void Tema1::resetPower()
{
	// Dimensiunea platformei
	if (board.w != boardWidth)
	{
		board.w = boardWidth;
		return;
	}

	// Viteza bilei
	if (ball.speed != initialSpeed)
	{
		ball.tx = ball.tx * 2;
		ball.ty = ball.ty * 2;
		ball.speed = initialSpeed;
		return;
	}
}

void Tema1::interpretPower()
{
	// Resetarea puterii anterioare(daca exista)
	resetPower();
	// Powerup tip 0 => +1 viata(maxim 4)
	if (powerType == 0)
	{
		if (lifes < 4)
		{
			lifes++;
		}
		powerTime = 0;
		return;
	}
	// Powerup tip 1 => platforma width = 5/4 * width
	if (powerType == 1)
	{
		board.w += boardWidth / 4;
		return;
	}
	// Powerup tip 2 => platforma width = 3/4 * width
	if (powerType == 2)
	{
		board.w -= boardWidth / 4;
		return;
	}
	// Powerup tip 3 => viteza bilei injumatatita
	if (powerType == 3)
	{
		ball.tx = ball.tx / 2;
		ball.ty = ball.ty / 2;
		ball.speed = initialSpeed / 2;
		return;
	}
}

void Tema1::FrameEnd()
{

}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{
}

void Tema1::OnKeyPress(int key, int mods)
{
}

void Tema1::OnKeyRelease(int key, int mods)
{
}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// Miscarea platformei
	board.corner.x = mouseX - board.w / 2;
	// Daca bila nu a fost lansata, miscarea si acesteia
	if (ball.inMovement == false) {
		ball.center.x = board.corner.x + board.w / 2;
	}
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// Punerea bilei in miscare
	if (ball.inMovement == false) {
		if (button == 1) {
			ball.inMovement = true;
		}
	}
	// Terminarea jocului fortata
	if (button == 2) {
		bricks.clear();
	}
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema1::OnWindowResize(int width, int height)
{
}
