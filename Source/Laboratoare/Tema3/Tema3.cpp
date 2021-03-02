#include "Tema3.h"

#include <vector>
#include <string>
#include <iostream>

#include <Core/Engine.h>

using namespace std;

Tema3::Tema3()
{
}

Tema3::~Tema3()
{
}

void Tema3::Init()
{
	const string textureLoc = "Source/Laboratoare/Tema3/Textures/";

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "player.png").c_str(), GL_REPEAT);
		mapTextures["player"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "fence_piece.png").c_str(), GL_REPEAT);
		mapTextures["fence"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "wood.jpg").c_str(), GL_REPEAT);
		mapTextures["wood"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "spike.jpg").c_str(), GL_REPEAT);
		mapTextures["spike"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "coin.png").c_str(), GL_REPEAT);
		mapTextures["coin"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "tile.jpg").c_str(), GL_REPEAT);
		mapTextures["tile"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "sky.jpg").c_str(), GL_REPEAT);
		mapTextures["sky"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "walkway.jpg").c_str(), GL_REPEAT);
		mapTextures["walkway"] = texture;
	}

	camera = new Labs::Camera();
	camera->Set(glm::vec3(0, 3, -12), glm::vec3(0, 1.5, -15.5f), glm::vec3(0, 1, 0));

	{
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("tile");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "tile.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("obstacle");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "obstacle.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("sphere");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "hq_sphere.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("fence");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "fence.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("coin");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "coin.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Shader* shader = new Shader("TileShader");
		shader->AddShader("Source/Laboratoare/Tema3/Shaders/TileShader.VS.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema3/Shaders/TileShader.FS.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	{
		Shader* shader = new Shader("DefaultShader");
		shader->AddShader("Source/Laboratoare/Tema3/Shaders/DefaultShader.VS.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema3/Shaders/DefaultShader.FS.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	{
		Shader* shader = new Shader("PlayerShader");
		shader->AddShader("Source/Laboratoare/Tema3/Shaders/PlayerShader.VS.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema3/Shaders/PlayerShader.FS.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	{
		Shader* shader = new Shader("HUDShader");
		shader->AddShader("Source/Laboratoare/Tema3/Shaders/HUDShader.VS.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema3/Shaders/HUDShader.FS.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	// mesh of a heart
	{
		vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(0, -1,  0), glm::vec3(0, 1, 1)),
			VertexFormat(glm::vec3(-2, 1,  0), glm::vec3(1, 0, 1)),
			VertexFormat(glm::vec3(-1,  2,  0), glm::vec3(0, 0, 1)),
			VertexFormat(glm::vec3(0,  1,  0), glm::vec3(1, 0, 1)),
			VertexFormat(glm::vec3(1,  2,  0), glm::vec3(1, 0, 1)),
			VertexFormat(glm::vec3(2,  1,  0), glm::vec3(1, 0, 1))
		};

		vector<unsigned short> indices =
		{
			0, 3, 1,
			1, 3, 2,
			3, 5, 4,
			0, 5, 3
		};

		Mesh* mesh = new Mesh("heart");
		mesh->InitFromData(vertices, indices);
		meshes[mesh->GetMeshID()] = mesh;

	}

	{
		vector<glm::vec3> vertices
		{
			glm::vec3(0,      0,     -1),
			glm::vec3(0.25   ,   0.5,  -1.25),
			glm::vec3(0.25   ,   0.5,  -0.75),
			glm::vec3(-0.25  ,   0.5,  -0.75),
			glm::vec3(-0.25  ,   0.5,  -1.25),
			glm::vec3(0.25   ,  -0.5,  -1.25),
			glm::vec3(0.25   ,  -0.5,  -0.75),
			glm::vec3(-0.25  ,  -0.5,  -0.75),
			glm::vec3(-0.25  ,  -0.5,  -1.25),

			glm::vec3(0,      0,     1),
			glm::vec3(0.25   ,   0.5,  1.25),
			glm::vec3(0.25   ,   0.5,  0.75),
			glm::vec3(-0.25  ,   0.5,  0.75),
			glm::vec3(-0.25  ,   0.5,  1.25),
			glm::vec3(0.25   ,  -0.5,  1.25),
			glm::vec3(0.25   ,  -0.5,  0.75),
			glm::vec3(-0.25  ,  -0.5,  0.75),
			glm::vec3(-0.25  ,  -0.5,  1.25),

			glm::vec3(0.1,      -0.1,   -2),
			glm::vec3(0.1,      0.1,    -2),
			glm::vec3(-0.1,      0.1,    -2),
			glm::vec3(-0.1,      -0.1,   -2),

			glm::vec3(0.1,      -0.1,    2),
			glm::vec3(0.1,      0.1,     2),
			glm::vec3(-0.1,      0.1,     2),
			glm::vec3(-0.1,      -0.1,    2),

			glm::vec3(0,      0,     -1),
			glm::vec3(0,      0,     1)
		};

		vector<glm::vec3> normals
		{
			glm::vec3(0, 0, 0),
			glm::vec3(0, -1, 0),
			glm::vec3(0, -1, 0),
			glm::vec3(0, -1, 0),
			glm::vec3(0, -1, 0),
			glm::vec3(0, 1, 0),
			glm::vec3(0, 1, 0),
			glm::vec3(0, 1, 0),
			glm::vec3(0, 1, 0),

			glm::vec3(0, 0, 0),
			glm::vec3(0, -1, 0),
			glm::vec3(0, -1, 0),
			glm::vec3(0, -1, 0),
			glm::vec3(0, -1, 0),
			glm::vec3(0, 1, 0),
			glm::vec3(0, 1, 0),
			glm::vec3(0, 1, 0),
			glm::vec3(0, 1, 0),

			glm::vec3(1, 0, 0),
			glm::vec3(1, 0, 0),

			glm::vec3(-1, 0, 0),
			glm::vec3(-1, 0, 0),

			glm::vec3(1, 0, 0),
			glm::vec3(1, 0, 0),

			glm::vec3(-1, 0, 0),
			glm::vec3(-1, 0, 0),
		};

		// TODO : Complete texture coordinates for the square
		vector<glm::vec2> textureCoords
		{
			glm::vec2(0.5f, 0.5f),
			glm::vec2(0.0f, 0.0f),
			glm::vec2(1.0f, 0.0f),
			glm::vec2(1.0f, 1.0f),
			glm::vec2(0.0f, 1.0f),
			glm::vec2(0.0f, 0.0f),
			glm::vec2(1.0f, 0.0f),
			glm::vec2(1.0f, 1.0f),
			glm::vec2(0.0f, 1.0f),

			glm::vec2(0.5f, 0.5f),
			glm::vec2(0.0f, 0.0f),
			glm::vec2(1.0f, 0.0f),
			glm::vec2(1.0f, 1.0f),
			glm::vec2(0.0f, 1.0f),
			glm::vec2(0.0f, 0.0f),
			glm::vec2(1.0f, 0.0f),
			glm::vec2(1.0f, 1.0f),
			glm::vec2(0.0f, 1.0f),

			glm::vec2(0.0f, 0.0f),
			glm::vec2(1.0f, 0.0f),
			glm::vec2(1.0f, 1.0f),
			glm::vec2(0.0f, 1.0f),
			glm::vec2(0.0f, 0.0f),
			glm::vec2(1.0f, 0.0f),
			glm::vec2(1.0f, 1.0f),
			glm::vec2(0.0f, 1.0f),

		};

		vector<unsigned short> indices =
		{
			0, 2, 1,
			0, 3, 2,
			0, 3, 4,
			0, 1, 4,
			0, 5, 6,
			0, 6, 7,
			0, 7, 8,
			0, 8, 5,
			3, 1, 2,
			1, 4, 3,
			6, 5, 7,
			7, 5, 8,

			9, 11, 10,
			9, 12, 11,
			9, 12, 13,
			9, 10, 13,
			9, 14, 15,
			9, 15, 16,
			9, 16, 17,
			9, 17, 14,
			12, 10, 11,
			10, 13, 12,
			15, 14, 16,
			16, 14, 17,

			18, 19, 20,
			20, 21, 18,
			18, 22, 23,
			18, 23, 19,
			22, 18, 25,
			25, 18, 21,
			23, 20, 19,
			24, 20, 23,
			20, 24, 21,
			21, 24, 25,
			22, 24, 23,
			22, 25, 24
		};

		Mesh* mesh = new Mesh("pillar");
		mesh->InitFromData(vertices, normals, textureCoords, indices);
		meshes[mesh->GetMeshID()] = mesh;

	}

	{
		vector<glm::vec3> vertices
		{
			glm::vec3(0,      0,     0),
			glm::vec3(0.25   ,   0.5,  -0.25),
			glm::vec3(0.25   ,   0.5,  0.25),
			glm::vec3(-0.25  ,   0.5,  0.25),
			glm::vec3(-0.25  ,   0.5,  -0.25),
			glm::vec3(0.25   ,  -0.5,  -0.25),
			glm::vec3(0.25   ,  -0.5,  0.25),
			glm::vec3(-0.25  ,  -0.5,  0.25),
			glm::vec3(-0.25  ,  -0.5,  -0.25),

		};

		vector<glm::vec3> normals
		{
			glm::vec3(0, 0, 0),
			glm::vec3(0, -1, 0),
			glm::vec3(0, -1, 0),
			glm::vec3(0, -1, 0),
			glm::vec3(0, -1, 0),
			glm::vec3(0, 1, 0),
			glm::vec3(0, 1, 0),
			glm::vec3(0, 1, 0),
			glm::vec3(0, 1, 0)
		};

		// TODO : Complete texture coordinates for the square
		vector<glm::vec2> textureCoords
		{
			glm::vec2(0.5f, 0.5f),
			glm::vec2(0.0f, 0.0f),
			glm::vec2(1.0f, 0.0f),
			glm::vec2(1.0f, 1.0f),
			glm::vec2(0.0f, 1.0f),
			glm::vec2(0.0f, 0.0f),
			glm::vec2(1.0f, 0.0f),
			glm::vec2(1.0f, 1.0f),
			glm::vec2(0.0f, 1.0f),
		};

		vector<unsigned short> indices =
		{
			0, 2, 1,
			0, 3, 2,
			0, 3, 4,
			0, 1, 4,
			0, 5, 6,
			0, 6, 7,
			0, 7, 8,
			0, 8, 5,
			3, 1, 2,
			1, 4, 3,
			6, 5, 7,
			7, 5, 8
		};

		Mesh* mesh = new Mesh("pillar2");
		mesh->InitFromData(vertices, normals, textureCoords, indices);
		meshes[mesh->GetMeshID()] = mesh;

	}

	{
		soundEngine = irrklang::createIrrKlangDevice();

		if (!soundEngine)
		{
			cout << "Could not startup engine\n";
		}


		soundEngine->setSoundVolume(0.1);
		soundEngine->play2D("Audio/sr_menu.ogg", true);
	}


	fov = RADIANS(60);
	projectionMatrix = glm::perspective(fov, window->props.aspectRatio, 0.01f, 800.0f);

	deque<Tile> t1, t2, t3;
	tiles.push_back(t1);
	tiles.push_back(t2);
	tiles.push_back(t3);

	deque<Decoration> t4, t5;
	decorations.push_back(t4);
	decorations.push_back(t5);

	for (int i = 0; i < numOfTiles; i++) {
		tiles[0].push_back(Tile(glm::vec3(-2 - distBetweenTiles, 1, -i * 4)));
		tiles[0][i].hasCollectible = false;
		tiles[0][i].hasObstacle = false;
		tiles[1].push_back(Tile(glm::vec3(0, 1, -i * 4)));
		tiles[1][i].hasCollectible = false;
		tiles[1][i].hasObstacle = false;
		tiles[2].push_back(Tile(glm::vec3(2 + distBetweenTiles, 1, -i * 4)));
		tiles[2][i].hasCollectible = false;
		tiles[2][i].hasObstacle = false;

		decorations[0].push_back(Decoration(glm::vec3(-4 - distBetweenTiles, 1, -i * 4), -2));
		decorations[1].push_back(Decoration(glm::vec3(4 + distBetweenTiles, 1, -i * 4), 2));
	}

	player = Player();
	player.position = playerInitPos;
	player.radius = 0.5;

	glm::ivec2 resolution = window->GetResolution();
	Text = new TextRenderer(resolution.x, resolution.y);

	Text->Load("Source/TextRenderer/Fonts/Arial.ttf", 30);
}

void Tema3::Reset()
{
	for(int i = 0; i < numOfColumns; i++)
		tiles[i].clear();
	for (int i = 0; i < numOfDecorCols; i++)
		decorations[i].clear();


	for (int i = 0; i < numOfTiles; i++) {
		tiles[0].push_back(Tile(glm::vec3(-2 - distBetweenTiles, 1, -i * 4)));
		tiles[0][i].hasCollectible = false;
		tiles[0][i].hasObstacle = false;
		tiles[1].push_back(Tile(glm::vec3(0, 1, -i * 4)));
		tiles[1][i].hasCollectible = false;
		tiles[1][i].hasObstacle = false;
		tiles[2].push_back(Tile(glm::vec3(2 + distBetweenTiles, 1, -i * 4)));
		tiles[2][i].hasCollectible = false;
		tiles[2][i].hasObstacle = false;

		decorations[0].push_back(Decoration(glm::vec3(-4 - distBetweenTiles, 1, -i * 4), -2));
		decorations[1].push_back(Decoration(glm::vec3(4 + distBetweenTiles, 1, -i * 4), 2));
	}

	player.position = playerInitPos;
	player.velocity = 0;
	player.crashed = false;

	speed = 10;

	camera->Set(glm::vec3(0, 3, -12), glm::vec3(0, 1.5, -15.5f), glm::vec3(0, 1, 0));
	deathTime = 0;

	lives = 3;
	score = 0;
}

void Tema3::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix,
	Texture2D* texture1, int renderedObject, int shaderOption)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	// Bind model matrix
	GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// Bind view matrix
	int loc_view_matrix = glGetUniformLocation(shader->program, "View");
	glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));

	// Bind projection matrix
	int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
	glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	glm::vec3 eyePosition = camera->position;
	int eye_position = glGetUniformLocation(shader->program, "eye_position");
	glUniform3f(eye_position, eyePosition.x, eyePosition.y, eyePosition.z);

	glm::vec3 lightDirections[64];
	glm::vec3 lightIntensities[64];
	glm::vec3 lightPositions[64];
	glm::vec3 lightColors[64];

	int hasLight[64];
	int isSpot[64];

	for (int i = 0; i < numOfDecorCols; i++)
		for (int j = 0; j < numOfTiles; j++)
		{
			lightDirections[16 * i + j] = decorations[i][j].lightDirection;
			lightIntensities[16 * i + j] = decorations[i][j].lightIntensity;
			lightPositions[16 * i + j] = decorations[i][j].lightPosition;
			lightColors[16 * i + j] = decorations[i][j].lightColor;

			hasLight[16 * i + j] = decorations[i][j].hasLight;
			isSpot[16 * i + j] = decorations[i][j].isSpot;
		}

	glUniform3fv(glGetUniformLocation(shader->program, "light_directions"), 64, glm::value_ptr(lightDirections[0]));
	glUniform3fv(glGetUniformLocation(shader->program, "light_intensities"), 64 , glm::value_ptr(lightIntensities[0]));
	glUniform3fv(glGetUniformLocation(shader->program, "light_positions"), 64, glm::value_ptr(lightPositions[0]));
	glUniform3fv(glGetUniformLocation(shader->program, "light_colors"), 64, glm::value_ptr(lightColors[0]));
	glUniform1iv(glGetUniformLocation(shader->program, "has_light"), 64, hasLight);
	glUniform1iv(glGetUniformLocation(shader->program, "is_spot"), 64, isSpot);

	glUniform1f(glGetUniformLocation(shader->program, "cutOffAngle"), spotCutoffAngle);

	if (renderedObject == PLAYER) 
	{
		glUniform3f(glGetUniformLocation(shader->program, "material_shininess"), player.materialShininess.x, player.materialShininess.y, player.materialShininess.z);
		glUniform3f(glGetUniformLocation(shader->program, "material_kd"), player.materialKd.x, player.materialKd.y, player.materialKd.z);
		glUniform3f(glGetUniformLocation(shader->program, "material_ks"), player.materialKs.x, player.materialKs.y, player.materialKs.z);
		glUniform3f(glGetUniformLocation(shader->program, "material_ke"), player.materialKe.x, player.materialKe.y, player.materialKe.z);
	}

	if (renderedObject == TILE) 
	{
		glUniform3f(glGetUniformLocation(shader->program, "material_shininess"), tiles[0][0].materialShininess.x, tiles[0][0].materialShininess.y, tiles[0][0].materialShininess.z);
		glUniform3f(glGetUniformLocation(shader->program, "material_kd"), tiles[0][0].materialKd.x, tiles[0][0].materialKd.y, tiles[0][0].materialKd.z);
		glUniform3f(glGetUniformLocation(shader->program, "material_ks"), tiles[0][0].materialKs.x, tiles[0][0].materialKs.y, tiles[0][0].materialKs.z);
		glUniform3f(glGetUniformLocation(shader->program, "material_ke"), tiles[0][0].materialKe.x, tiles[0][0].materialKe.y, tiles[0][0].materialKe.z);
	}

	if (renderedObject == DECORATION) 
	{
		glUniform3f(glGetUniformLocation(shader->program, "material_shininess"), decorations[0][0].materialShininess.x, decorations[0][0].materialShininess.y, decorations[0][0].materialShininess.z);
		glUniform3f(glGetUniformLocation(shader->program, "material_kd"), decorations[0][0].materialKd.x, decorations[0][0].materialKd.y, decorations[0][0].materialKd.z);
		glUniform3f(glGetUniformLocation(shader->program, "material_ks"), decorations[0][0].materialKs.x, decorations[0][0].materialKs.y, decorations[0][0].materialKs.z);
		glUniform3f(glGetUniformLocation(shader->program, "material_ke"), decorations[0][0].materialKe.x, decorations[0][0].materialKe.y, decorations[0][0].materialKe.z);
	}


	if (shader->GetName() == shaders["PlayerShader"]->GetName())
	{
		glUniform1i(glGetUniformLocation(shader->program, "is_powered_up"), shaderOption);
		glUniform1f(glGetUniformLocation(shader->program, "time"), Engine::GetElapsedTime());

	}
	
	if (shader->GetName() == shaders["TileShader"]->GetName())
	{
		glUniform1i(glGetUniformLocation(shader->program, "type"), shaderOption);
	}
		

	if (texture1)
	{
		//TODO : activate texture location 0
		glActiveTexture(GL_TEXTURE0);
		//TODO : Bind the texture1 ID
		glBindTexture(GL_TEXTURE_2D, texture1->GetTextureID());
		//TODO : Send texture uniform value
		glUniform1i(glGetUniformLocation(shader->program, "texture_1"), 0);
	}

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);

}

void Tema3::RenderHUD()
{
	// render lives left
	{
		glm::mat4 modelMatrix = glm::mat4(1);

		modelMatrix = glm::translate(modelMatrix, glm::vec3(0.93, 0.89, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.04, 0.04, 1));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(1 / 1.77, 1, 1));
		if (lives >= 1)
			RenderMesh(meshes["heart"], shaders["HUDShader"], modelMatrix);

		modelMatrix = glm::translate(modelMatrix, glm::vec3(-5, 0, 0));
		if (lives >= 2)
			RenderMesh(meshes["heart"], shaders["HUDShader"], modelMatrix);

		modelMatrix = glm::translate(modelMatrix, glm::vec3(-5, 0, 0));
		if (lives >= 3)
			RenderMesh(meshes["heart"], shaders["HUDShader"], modelMatrix);
	}
}

void Tema3::CheckGameOver(float deltaTimeSeconds)
{
	if (lives == 0) {
		if (score > highScore)
			highScore = score;
		deathTime = Engine::GetElapsedTime();
	} 
	else if (hasCrashed == true)
	{
		lives--;
		hasCrashed = false;
	}

	// reduce speed to end the game
	if (deathTime > 0)
	{
		if (speed > 0.2)
			speed -= deltaTimeSeconds * 10;
		else
			canRestart = true;
	}
}

void Tema3::UpdateTiles(float deltaTimeSeconds)
{
	// move and render tiles
	bool outside = false;
	int vanishPos = 2;

	for (int j = 0; j < numOfColumns; j++)
		for (int i = 0; i < numOfTiles; i++)
		{
			tiles[j][i].move(deltaTimeSeconds * speed, deltaTimeSeconds);

			tiles[j][i].isCurrent = (i == 4 && player.testCollision(tiles[j][i]));

			RenderSimpleMesh(meshes[tiles[j][i].type], shaders[tiles[j][i].shader], tiles[j][i].modelMatrix, mapTextures[tiles[j][i].texture], TILE);

			if(tiles[j][i].hasObstacle && tiles[j][i].type != "")
				RenderSimpleMesh(meshes["obstacle"], shaders[tiles[j][i].shader], tiles[j][i].obsModelMatrix, mapTextures["spike"], TILE);

			if (tiles[j][i].position.z > vanishPos)
				outside = true;

			if(tiles[j][i].hasCollectible && !tiles[j][i].collected)
				RenderSimpleMesh(meshes["coin"], shaders[tiles[j][i].shader], tiles[j][i].collectibleModelMatrix, mapTextures["coin"], TILE, 1);


			if (!tiles[j][i].collected && !deathTime && tiles[j][i].hasCollectible && player.testCollectCollision(tiles[j][i])) 
			{
				soundEngine->play2D("Audio/collect.wav");
				score++;
			}
		}

	for (int j = 0; j < numOfDecorCols; j++)
		for (int i = 0; i < numOfTiles; i++)
		{
			decorations[j][i].move(deltaTimeSeconds * speed);
			RenderSimpleMesh(meshes[decorations[j][i].floorMesh], shaders[decorations[j][i].shader], decorations[j][i].modelMatrix,
				mapTextures[decorations[j][i].floorTexture], TILE);
			RenderSimpleMesh(meshes[decorations[j][i].mesh], shaders[decorations[j][i].shader], decorations[j][i].decModelmatrix,
				mapTextures["fence"], DECORATION, 2);

			if (decorations[j][i].mesh == "pillar2")
			{
				glm::mat4 modelMatrix = decorations[j][i].decModelmatrix;
				modelMatrix = glm::translate(modelMatrix, glm::vec3(0, -1, 0));

				RenderSimpleMesh(meshes[decorations[j][i].mesh], shaders[decorations[j][i].shader], modelMatrix,
					mapTextures["fence"], DECORATION, 2);

				modelMatrix = glm::translate(modelMatrix, glm::vec3(0, -1, 0));

				RenderSimpleMesh(meshes[decorations[j][i].mesh], shaders[decorations[j][i].shader], modelMatrix,
					mapTextures["fence"], DECORATION, 2);

				modelMatrix = glm::translate(modelMatrix, glm::vec3(0, -1, 0));

				RenderSimpleMesh(meshes[decorations[j][i].mesh], shaders[decorations[j][i].shader], modelMatrix,
					mapTextures["fence"], DECORATION, 2);
			}
			
		}

	// delete out of view tiles
	if (outside)
	{
		float offset = tiles[0][0].position.z - vanishPos;
		for (int i = 0; i < numOfColumns; i++)
			tiles[i].pop_front();
		for (int i = 0; i < numOfDecorCols; i++)
			decorations[i].pop_front();

		
		tiles[0].push_back(Tile(glm::vec3(-2 - distBetweenTiles, 1, (-4 * numOfTiles) + vanishPos + offset)));
		tiles[1].push_back(Tile(glm::vec3(0, 1, (-4 * numOfTiles) + vanishPos + offset)));
		tiles[2].push_back(Tile(glm::vec3(2 + distBetweenTiles, 1, (-4 * numOfTiles) + vanishPos + offset)));

		decorations[0].push_back(Decoration(glm::vec3(-4 - distBetweenTiles, 1, (-4 * numOfTiles) + vanishPos + offset), -2));
		decorations[1].push_back(Decoration(glm::vec3(4 + distBetweenTiles, 1, (-4 * numOfTiles) + vanishPos + offset), 2));
	}
}

void Tema3::RenderPlayer(float deltaTimeSeconds)
{
	// render player, and apply gravity

	glm::mat4 modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, player.position);
	modelMatrix = glm::rotate(modelMatrix, deltaTimeSeconds * speed, glm::vec3(1, 0, 0));


	if (!player.crashed)
	{
		if (player.applyGravity(deltaTimeSeconds, tiles[player.getColumn()][4]))
		{
			if (!deathTime)
				soundEngine->play2D("Audio/crash.ogg");

			hasCrashed = true;
		}
	}
	else
	{

		if (!player.applyGravity(deltaTimeSeconds, tiles[player.getColumn()][4]))
			player.crashed = false;
	}

	
	if(lives == 0)
		modelMatrix = glm::scale(modelMatrix, glm::vec3(speed / speedLimit, speed / speedLimit, speed / speedLimit));


	std::random_device rd; // obtain a random number from hardware
	std::mt19937 gen(rd()); // seed the generator
	std::uniform_int_distribution<> distr(1, 20);

	if (!isFirstPerson)
		if (player.crashed || lives == 0 || player.position.y < 0.9)
		{
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.3, 0.3, 0.3));
			RenderSimpleMesh(meshes["sphere"], shaders["PlayerShader"], modelMatrix, NULL, 0, distr(gen));
		}
		else
		{
			RenderSimpleMesh(meshes["sphere"], shaders["PlayerShader"], modelMatrix, mapTextures["player"]);
		}
}

void Tema3::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);

	glm::mat4 modelMatrix = glm::mat4(1);
	modelMatrix = glm::scale(modelMatrix, glm::vec3(700, 700, 700));
	RenderSimpleMesh(meshes["box"], shaders["DefaultShader"], modelMatrix, mapTextures["sky"]);
}


void Tema3::Update(float deltaTimeSeconds)
{
	RenderHUD();
	CheckGameOver(deltaTimeSeconds);
	UpdateTiles(deltaTimeSeconds);
	RenderPlayer(deltaTimeSeconds);
	if(!deathTime)
		speed += deltaTimeSeconds / 10;
}

void Tema3::FrameEnd()
{
	Text->RenderText("Score: " + to_string(score), 5.0f, 5.0f, 1.0f, glm::vec3(1.0, 1.0, 1.0));
	Text->RenderText("High Score: " + to_string(highScore), 5.0f, 40.0f, 1.0f, glm::vec3(1.0, 1.0, 1.0));


	if (deathTime > 0)
	{
		Text->RenderText("Game Over", 570.0f, 320.0f, 1.0f, glm::vec3(1.0, 1.0, 1.0));
		Text->RenderText("Press SPACE to restart", 490.0f, 360.0f, 1.0f, glm::vec3(1.0, 1.0, 1.0));
	}
}

void Tema3::OnInputUpdate(float deltaTime, int mods)
{
	if (window->KeyHold(GLFW_KEY_A) && !deathTime)
	{
		if (player.position.x > -2.5)
			player.position.x -= deltaTime * 5;
		else
			player.position.x = -2.5;
	}

	if (window->KeyHold(GLFW_KEY_D) && !deathTime)
	{
		if (player.position.x < 2.5)
			player.position.x += deltaTime * 5;
		else
			player.position.x = 2.5;
	}

	if (window->KeyHold(GLFW_KEY_SPACE))
	{
		if (player.velocity == 0 && !deathTime)
		{
			player.velocity = - 0.07;
		}

		if (canRestart)
		{
			Reset();
			canRestart = false;
		}
	}
}

void Tema3::OnKeyPress(int key, int mods)
{

}

void Tema3::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Tema3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	
}

void Tema3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Tema3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Tema3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema3::OnWindowResize(int width, int height)
{
}
