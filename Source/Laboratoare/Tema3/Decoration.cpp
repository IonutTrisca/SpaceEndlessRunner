#include "Decoration.h"


Decoration::Decoration(glm::vec3 position, int column)
{
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 gen(rd()); // seed the generator
	std::uniform_int_distribution<> distr(0, 255); // define the range

	int a = distr(gen);
	

	this->position = position;
	modelMatrix = glm::translate(glm::mat4(1), position);
	decModelmatrix = modelMatrix;
	decModelmatrix = glm::translate(decModelmatrix, glm::vec3(0, 0.05 + 0.5, 0));

	this->column = column;
	this->hasLight = hasLight;
	
	hasLight = a < 100 ? true : false;

	a = distr(gen);

	if (a < 128)
		this->mesh = "pillar2";
	else
		this->mesh = "pillar";

	hasLight = true;

	if (hasLight)
	{
		if (column > 0)
			lightDirection = glm::vec3(-1, 0, 0);
		else
			lightDirection = glm::vec3(1, 0, 0);

		lightColor.x = a / 255.0;
		a = distr(gen);
		lightColor.y = a / 255.0;
		a = distr(gen);
		lightColor.z = a / 255.0;

		if (this->mesh == "pillar")
			isSpot = true;
		else
			isSpot = false;

		if (isSpot)
			lightIntensity = glm::vec3(20);
	}
	
}

Decoration::~Decoration()
{
}

void Decoration::move(float movement)
{
	position.z += movement;
	modelMatrix = glm::translate(glm::mat4(1), position);
	decModelmatrix = modelMatrix;
	decModelmatrix = glm::translate(decModelmatrix, glm::vec3(0, 0.05 + 0.5, 0));

	if (hasLight)
	{
		if(!isSpot)
			lightPosition = glm::vec3(position.x , position.y + 1, position.z);
		else
			lightPosition = glm::vec3(position.x, position.y + 0.55, position.z + 1);
	}

	if (mesh == "pillar2")
	{
		decModelmatrix = modelMatrix;
		decModelmatrix = glm::translate(decModelmatrix, glm::vec3(0, 0.05 + 0.5, 1.5));
		decModelmatrix = glm::rotate(decModelmatrix, RADIANS(90), glm::vec3(1, 0, 0));
	}
}