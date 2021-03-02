#pragma once
#include <Core/Engine.h>

#include <string>
#include <random>

class Tile 
{
public:
	Tile(glm::vec3 position);
	~Tile();

	void move(float movement, float time);
	int getColumn();

	glm::vec3 position;
	std::string type = "tile";
	std::string texture = "tile";
	glm::mat4 modelMatrix;
	glm::mat4 obsModelMatrix;
	glm::mat4 collectibleModelMatrix;
	std::string shader = "TileShader";
	float rotation = 0;
	float collVerticalPos = 0;
	float collRadius = 0.5;
	int shaderType = 2;
	bool isCurrent = false;
	bool wasTouched = false;
	bool isPowerActive = false;

	bool hasCollectible = false;
	bool collected = false;
	bool goingDown = true;

	int speed;

	bool hasObstacle;

	glm::vec3 materialShininess = glm::vec3(10);
	glm::vec3 materialKd = glm::vec3(0.5, 0.5, 0.5);
	glm::vec3 materialKs = glm::vec3(0.5, 0.5, 0.5);
	glm::vec3 materialKe = glm::vec3(0);
};