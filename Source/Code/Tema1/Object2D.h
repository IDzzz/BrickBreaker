#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

namespace Object2D
{

	// Create square with given bottom left corner, length and color
	//Mesh* CreateSquare(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);

	Mesh* CreateMyRectangle(std::string name, glm::vec3 leftBottomCorner, float l, float L, glm::vec3 color, bool fill = false);
	Mesh* CreateMyCircle(std::string name, float radius, glm::vec3 color);
	Mesh* CreateGG(std::string name, glm::vec3 leftBottomCorner, float width, float height, glm::vec3 color);


}

