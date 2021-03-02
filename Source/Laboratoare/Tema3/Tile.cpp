#include "Tile.h"

Tile::Tile(glm::vec3 position)
{
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 gen(rd()); // seed the generator
	std::uniform_int_distribution<> distr(1, 25); // define the range

	int a = distr(gen);

	speed = distr(gen);

	hasObstacle = a < 3 ? true : false;

	if (!hasObstacle)
	{
		a = distr(gen);
		hasCollectible = a < 5 ? true : false;
		collVerticalPos = 0.2 + 1.0 / speed;
	}

	this->position = position;
	modelMatrix = glm::translate(glm::mat4(1), position);
	obsModelMatrix = glm::translate(glm::mat4(1), position);
	obsModelMatrix = glm::translate(obsModelMatrix, glm::vec3(0,0.30,0));
	collectibleModelMatrix = glm::translate(glm::mat4(1), position);
	collectibleModelMatrix = glm::translate(collectibleModelMatrix, glm::vec3(0, collVerticalPos, 0));
	this->type = type;
	this->hasObstacle = hasObstacle;
}

Tile::~Tile()
{
}

void Tile::move(float movement, float time)
{
	position.z += movement;
	rotation += time;
	modelMatrix = glm::translate(glm::mat4(1), position);
	obsModelMatrix = glm::translate(glm::mat4(1), position);
	obsModelMatrix = glm::translate(obsModelMatrix, glm::vec3(0, 0.30, 0));
	collectibleModelMatrix = glm::translate(glm::mat4(1), position);
	collectibleModelMatrix = glm::translate(collectibleModelMatrix, glm::vec3(0, collVerticalPos, 0));
	collectibleModelMatrix = glm::rotate(collectibleModelMatrix, rotation, glm::vec3(0, 1, 0));


	if (collVerticalPos < 0.5)
		goingDown = false;

	if (collVerticalPos > 1)
		goingDown = true;

	if (goingDown)
		collVerticalPos -= time;
	else 
		collVerticalPos += time;

	//collectibleModelMatrix = glm::translate(collectibleModelMatrix, glm::vec3(0, collVerticalPos, 0));

}

int Tile::getColumn()
{
	if (position.x < -1)
		return 0;
	if (position.x > 1)
		return 2;
	return 1;
}