#pragma once
#include <Core/Engine.h>
#include <cmath>
#include <Core/Audio/irrKlang.h>
#include <iostream>

#include "Tile.h"

class Player
{
public:
	Player();
	Player(glm::vec3 position);
	~Player();

	bool applyGravity(float deltaTimeSeconds, Tile& tile);
	bool testCollision(Tile& tile);
	bool testObsCollision(Tile& tile);
	int getColumn();
	bool testCollectCollision(Tile& tile);

	glm::vec3 position;
	float velocity = 0;
	float radius;
	bool crashed = false;

	glm::vec3 materialShininess = glm::vec3(30, 30, 30);
	glm::vec3 materialKd = glm::vec3(0.5, 0.5, 0.5);
	glm::vec3 materialKs = glm::vec3(0.5, 0.5, 0.5);
	glm::vec3 materialKe = glm::vec3(0);
}; 