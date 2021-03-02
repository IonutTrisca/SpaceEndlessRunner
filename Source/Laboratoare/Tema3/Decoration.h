#pragma once
#include <Core/Engine.h>
#include "Tile.h"
#include <string>
#include <random>

class Decoration
{
public:
	Decoration(glm::vec3 position, int column);
	~Decoration();

	void move(float movement);

	glm::vec3 position;
	std::string mesh;
	std::string floorMesh = "tile";
	std::string floorTexture = "walkway";
	std::string texture = "tile";
	glm::mat4 modelMatrix;
	glm::mat4 decModelmatrix;

	int column;
	std::string shader = "TileShader";
	bool hasLight;

	glm::vec3 lightPosition;
	glm::vec3 lightDirection;
	glm::vec3 lightIntensity = glm::vec3(5);
	glm::vec3 lightColor;

	glm::vec3 materialShininess = glm::vec3(30);
	glm::vec3 materialKd = glm::vec3(0.5, 0.5, 0.5);
	glm::vec3 materialKs = glm::vec3(0.5, 0.5, 0.5);
	glm::vec3 materialKe = glm::vec3(0.5);

	int isSpot;
	float spotCutoffAngle;
};