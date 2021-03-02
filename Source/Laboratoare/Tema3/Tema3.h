#pragma once
#include <Component/SimpleScene.h>
#include <Core/Audio/irrKlang.h>
#include <deque>
#include <random>
#include "Camera.h"
#include "Tile.h"
#include "Player.h"
#include "Decoration.h"

#include <TextRenderer/TextRenderer.h>

#define PLAYER 0
#define TILE 1
#define DECORATION 2

class Tema3 : public SimpleScene
{
public:
	Tema3();
	~Tema3();

	void Init() override;

private:
	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;

	void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, Texture2D* texture1 = NULL, int renderedObject = 0 ,int shaderOption = 0);

	void OnInputUpdate(float deltaTime, int mods) override;
	void OnKeyPress(int key, int mods) override;
	void OnKeyRelease(int key, int mods) override;
	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
	void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
	void OnWindowResize(int width, int height) override;

	void Reset();
	void RenderHUD();
	void CheckGameOver(float deltaTimeSeconds);
	void UpdateTiles(float deltaTimeSeconds);
	void RenderPlayer(float deltaTimeSeconds);

protected:
	Labs::Camera* camera;
	glm::mat4 projectionMatrix;
	bool renderCameraTarget;
	float fov;
	irrklang::ISoundEngine* soundEngine;
	float speed = 10;
	float speedLimit = 16;
	std::deque<std::deque<Tile>> tiles;
	std::deque<std::deque<Decoration>> decorations;
	int numOfDecorCols = 2;

	Player player;
	long long numOfTiles = 16;
	int numOfColumns = 3;
	bool isFirstPerson = false;
	int distBetweenTiles = 0;
	float deathTime = 0;
	glm::vec3 playerInitPos = glm::vec3(0, 3, -16);
	int lives = 3;
	int score = 0;
	int highScore = 0;

	std::unordered_map<std::string, Texture2D*> mapTextures;
	TextRenderer* Text;
	bool canRestart = false;
	bool hasCrashed = false;
	float spotCutoffAngle = 60;
};
