#include "GameManager.h"

void GameManager::StartGame()
{

	Shader newShader("../Shaders/ShaderVS.vs", "../Shaders/ShaderFS.fs");
	shader = newShader;

	this->widht = widht;
	this->height = height;
	int spriteWidth, spriteHeight;
	GLuint texIdle = SetupTexture("../../textures/characters/PNG/Rogue/Run_Attack/green.png", spriteWidth, spriteHeight);
	
	character.InitializeSprite(1, 1);
	character.SetTexId(texIdle);
	character.SetPosition(glm::vec3(32.0, 32.0, 0.0));
	character.SetDimension(glm::vec3(spriteWidth, spriteHeight, 0));
	character.SetShader(&shader);

	GLuint texBd = SetupTexture("../../textures/backgrounds/PNG/Postapocalypce4/Pale/postapocalypse4.png", spriteWidth, spriteHeight);

	background.InitializeSprite(1, 1);
	background.SetTexId(texBd);
	background.SetPosition(glm::vec3(400.0, 300.0, 0));
	background.SetDimension(glm::vec3(spriteWidth / 2, spriteHeight / 2, 0));
	background.SetShader(&shader);

	GLuint texWall = SetupTexture("../../textures/characters/PNG/Rogue/Run_Attack/red.png", spriteWidth, spriteHeight);

	mazeWall.InitializeSprite(1, 1);
	mazeWall.SetTexId(texWall);
	mazeWall.SetDimension(glm::vec3(spriteWidth, spriteHeight, 0));
	mazeWall.SetShader(&shader);
}

void GameManager::Draw()
{
	background.DrawSprite();
	character.DrawSprite();
	mazeWall.DrawSprite();
}

void GameManager::Update()
{
	background.UpdateSprite();
	character.UpdateSprite();
	mazeWall.UpdateSprite();

	for (int x = 0; x < 10; x++)
	{
		mazeWall.SetPosition(glm::vec3(x * 32.0, 288.0, 0));
		mazeWall.UpdateSprite();
		mazeWall.DrawSprite();

		if (mazeWall.CheckColision(character))
		{
			character.SetPosition(glm::vec3(64.0, 64.0, 0.0));
		}

		mazeWall.SetPosition(glm::vec3(x * 32.0, 488.0, 0));
		mazeWall.UpdateSprite();
		mazeWall.DrawSprite();

		if (mazeWall.CheckColision(character))
		{
			character.SetPosition(glm::vec3(64.0, 64.0, 0.0));
		}
	}
}

int GameManager::SetupTexture(string filePath, int& width, int& height)
{
	GLuint texID;

	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	int nrChannels;
	unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);

	if (data)
	{
		if (nrChannels == 3) //jpg, bmp
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		else //png
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);

	glBindTexture(GL_TEXTURE_2D, 0);

	return texID;
}
