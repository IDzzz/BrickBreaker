#include "Object2D.h"
#include <Core/Engine.h>

// Mesha dreptunghi(laborator)
Mesh* Object2D::CreateMyRectangle(std::string name, glm::vec3 leftBottomCorner, float width, float height, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(height, 0, 0), color),
		VertexFormat(corner + glm::vec3(height, width, 0), color),
		VertexFormat(corner + glm::vec3(0, width, 0), color)
	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3 };

	if (!fill) {
		square->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		// draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(2);
	}

	square->InitFromData(vertices, indices);
	return square;
}

// Mesha pentru litera G
Mesh * Object2D::CreateGG(std::string name, glm::vec3 leftBottomCorner, float width, float height, glm::vec3 color)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner + glm::vec3(width, height, 0), color),
		VertexFormat(corner + glm::vec3(0, height, 0), color),
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(width, 0, 0), color),
		VertexFormat(corner + glm::vec3(width, height / 2, 0), color),
		VertexFormat(corner + glm::vec3(width / 2, height / 2, 0), color),
	};

	std::vector<unsigned short> indices = {0, 1, 2, 3, 4, 5};

	glLineWidth(4);
	Mesh* g = new Mesh(name);
	g->SetDrawMode(GL_LINE_STRIP);


	g->InitFromData(vertices, indices);
	return g;
}

// Mesha pentru disc
Mesh * Object2D::CreateMyCircle(std::string name, float radius, glm::vec3 color)
{
	std::vector<VertexFormat> vertices;
	std::vector<unsigned short> indices;

	for (int u = -360; u <= 360; u++) 
	{
		vertices.push_back(VertexFormat::VertexFormat(glm::vec3(radius * sin(u * 3.14 / 360), radius * cos(u * 3.14 / 360), 0), color));
	}

	for (unsigned short i = 0; i < vertices.size(); i++)
	{
		indices.push_back(i);
	}

	Mesh* circle = new Mesh(name);
	circle->SetDrawMode(GL_POLYGON);


	circle->InitFromData(vertices, indices);
	return circle;
}
