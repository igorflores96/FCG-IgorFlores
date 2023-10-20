#include <iostream>
#include <string>
#include <assert.h>
#include <stb_image.h>
#include "KeysManager.h"
#include "Timer.h"

using namespace std;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

int setupTexture(string filePath, int& width, int& height);

Sprite character, background, background2, background3, background4, mazeWall, key1, key2, key3, gate;
KeysManager managerKey;
Timer timer;

const GLuint WIDTH = 800, HEIGHT = 600;

void DrawMazeWall(float posX, float posY)
{
	mazeWall.SetPosition(glm::vec3(posX * 32, posY * 32, 0));
	mazeWall.UpdateSprite();
	mazeWall.DrawSprite();

	if (mazeWall.CheckColision(character))
	{
		character.SetPosition(glm::vec3(17 * 32.0, 4 * 32.0, 0.0));
	}
}
void DrawMaze()
{
	//Bottom Line
	for (int x = 6; x < 19; x++) { DrawMazeWall(x, 3); }

	//Top Line
	for (int x = 6; x < 19; x++) { DrawMazeWall(x, 15); }

	//Left Line
	for (int y = 4; y < 15; y++) { DrawMazeWall(6, y); }

	//Right Line
	for (int y = 4; y < 15; y++) { DrawMazeWall(18, y); }

	//Inside Lines (Left to Right - Top to bottom)
	DrawMazeWall(14, 14);

	DrawMazeWall(7, 13);
	DrawMazeWall(8, 13);
	DrawMazeWall(9, 13);
	DrawMazeWall(10, 13);
	DrawMazeWall(12, 13);
	DrawMazeWall(14, 13);
	DrawMazeWall(16, 13);

	DrawMazeWall(10, 12);
	DrawMazeWall(12, 12);
	DrawMazeWall(16, 12);

	DrawMazeWall(8, 11);
	DrawMazeWall(9, 11);
	DrawMazeWall(10, 11);
	DrawMazeWall(12, 11);
	DrawMazeWall(13, 11);
	DrawMazeWall(14, 11);
	DrawMazeWall(15, 11);
	DrawMazeWall(16, 11);

	DrawMazeWall(10, 10);

	DrawMazeWall(7, 9);
	DrawMazeWall(8, 9);
	DrawMazeWall(10, 9);
	DrawMazeWall(12, 9);
	DrawMazeWall(14, 9);
	DrawMazeWall(15, 9);
	DrawMazeWall(16, 9);

	DrawMazeWall(12, 8);
	DrawMazeWall(16, 8);

	DrawMazeWall(7, 7);
	DrawMazeWall(8, 7);
	DrawMazeWall(9, 7);
	DrawMazeWall(10, 7);
	DrawMazeWall(11, 7);
	DrawMazeWall(12, 7);
	DrawMazeWall(13, 7);
	DrawMazeWall(14, 7);
	DrawMazeWall(16, 7);

	DrawMazeWall(16, 6);

	DrawMazeWall(8, 5);
	DrawMazeWall(9, 5);
	DrawMazeWall(10, 5);
	DrawMazeWall(12, 5);
	DrawMazeWall(13, 5);
	DrawMazeWall(14, 5);
	DrawMazeWall(15, 5);
	DrawMazeWall(16, 5);
	DrawMazeWall(17, 5);

	DrawMazeWall(10, 4);
}

int main()
{

	glfwInit();


	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Trabalho GA - Igor Flores e Tiago Gazolla", nullptr, nullptr);
	glfwMakeContextCurrent(window);


	glfwSetKeyCallback(window, key_callback);


	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;

	}

	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* version = glGetString(GL_VERSION);
	cout << "Renderer: " << renderer << endl;
	cout << "OpenGL version supported " << version << endl;

	Shader shader("../Shaders/ShaderVS.vs", "../Shaders/ShaderFS.fs");

	int spriteWidth, spriteHeight;
	GLuint tex = setupTexture("../Sprites/Mage.png", spriteWidth, spriteHeight);

	character.InitializeSprite(5, 4);
	character.SetTexId(tex);
	character.SetAnimation(1);
	character.SetPosition(glm::vec3(17 * 32.0, 4 * 32.0, 0.0));
	character.SetDimension(glm::vec3(spriteWidth, spriteHeight, 0));
	character.SetShader(&shader);

	tex = setupTexture("../Sprites/BackgroundClouds.png", spriteWidth, spriteHeight);

	background.InitializeSprite(1, 1);
	background.SetTexId(tex);
	background.SetSpeed(0.5);
	background.SetPosition(glm::vec3(400.0, 300.0, 0));
	background.SetDimension(glm::vec3(spriteWidth / 2, spriteHeight / 2, 0));
	background.SetShader(&shader);

	tex = setupTexture("../Sprites/BackgroundClouds.png", spriteWidth, spriteHeight);

	background2.InitializeSprite(1, 1);
	background2.SetTexId(tex);
	background2.SetSpeed(0.5);
	background2.SetPosition(glm::vec3(-560.0, 300.0, 0));
	background2.SetDimension(glm::vec3(spriteWidth / 2, spriteHeight / 2, 0));
	background2.SetShader(&shader);

	tex = setupTexture("../Sprites/BackgroundFloor.png", spriteWidth, spriteHeight);

	background3.InitializeSprite(1, 1);
	background3.SetTexId(tex);
	background3.SetSpeed(2.0);
	background3.SetPosition(glm::vec3(400.0, 300.0, 0));
	background3.SetDimension(glm::vec3(spriteWidth / 2, spriteHeight / 2, 0));
	background3.SetShader(&shader);

	tex = setupTexture("../Sprites/BackgroundFloor.png", spriteWidth, spriteHeight);

	background4.InitializeSprite(1, 1);
	background4.SetTexId(tex);
	background4.SetSpeed(2.0);
	background4.SetPosition(glm::vec3(-560.0, 300.0, 0));
	background4.SetDimension(glm::vec3(spriteWidth / 2, spriteHeight / 2, 0));
	background4.SetShader(&shader);



	tex = setupTexture("../Sprites/Flame.png", spriteWidth, spriteHeight);

	mazeWall.InitializeSprite(1, 2);
	mazeWall.SetTexId(tex);
	mazeWall.SetDimension(glm::vec3(spriteWidth, spriteHeight, 0));
	mazeWall.SetShader(&shader);

	tex = setupTexture("../../textures/characters/PNG/Rogue/Run_Attack/blue.png", spriteWidth, spriteHeight);

	key1.InitializeSprite(1, 1);
	key1.SetTexId(tex);
	key1.SetPosition(glm::vec3(17 * 32.0, 6 * 32.0, 0.0));
	key1.SetDimension(glm::vec3(spriteWidth, spriteHeight, 0));
	key1.SetShader(&shader);

	key2.InitializeSprite(1, 1);
	key2.SetTexId(tex);
	key2.SetPosition(glm::vec3(7 * 32.0, 14 * 32.0, 0.0));
	key2.SetDimension(glm::vec3(spriteWidth, spriteHeight, 0));
	key2.SetShader(&shader);

	key3.InitializeSprite(1, 1);
	key3.SetTexId(tex);
	key3.SetPosition(glm::vec3(9 * 32.0, 12 * 32.0, 0.0));
	key3.SetDimension(glm::vec3(spriteWidth, spriteHeight, 0));
	key3.SetShader(&shader);

	tex = setupTexture("../../textures/characters/PNG/Rogue/Run_Attack/green.png", spriteWidth, spriteHeight);

	gate.InitializeSprite(1, 1);
	gate.SetTexId(tex);
	gate.SetPosition(glm::vec3(9 * 32.0, 4 * 32.0, 0.0));
	gate.SetDimension(glm::vec3(spriteWidth, spriteHeight, 0));
	gate.SetShader(&shader);


	shader.Use();

	glm::mat4 projection = glm::ortho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);
	shader.setMat4("projection", glm::value_ptr(projection));
	glActiveTexture(GL_TEXTURE0);
	shader.setInt("texBuffer", 0);

	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_ALWAYS);

	while (!glfwWindowShouldClose(window))
	{
		timer.Start();

		glfwPollEvents();

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		
		background.UpdateSprite();
		background.DrawSprite();
		background.MoveRight();
		if (background.GetPosition().x > 1280.0) { background.SetPosition(glm::vec3(-635.0, 300.0, 0)); }
			
		background2.UpdateSprite();
		background2.DrawSprite();
		background2.MoveRight();
		if (background2.GetPosition().x > 1280.0) { background2.SetPosition(glm::vec3(-635.0, 300.0, 0)); }
			
		background3.UpdateSprite();
		background3.DrawSprite();
		background3.MoveRight();
		if (background3.GetPosition().x > 1280.0) { background3.SetPosition(glm::vec3(-635.0, 300.0, 0)); }

		background4.UpdateSprite();
		background4.DrawSprite();
		background4.MoveRight();
		if (background4.GetPosition().x > 1280.0) { background4.SetPosition(glm::vec3(-635.0, 300.0, 0)); }
			
		character.UpdateSprite();
		character.DrawSprite();
		
		DrawMaze();

		if (!key1.HasColected())
		{
			key1.UpdateSprite();
			key1.DrawSprite();

			if (managerKey.CheckColision(key1, character))
			{
				managerKey.AddKey();
				key1.SetPosition(glm::vec3(20 * 32.0, 17 * 32.0, 0.0));
			}
		}

		if (!key2.HasColected())
		{
			key2.UpdateSprite();
			key2.DrawSprite();

			if (managerKey.CheckColision(key2, character))
			{
				managerKey.AddKey();
				key2.SetPosition(glm::vec3(22 * 32.0, 17 * 32.0, 0.0));
			}
		}

		if (!key3.HasColected())
		{
			key3.UpdateSprite();
			key3.DrawSprite();

			if (managerKey.CheckColision(key3, character))
			{
				managerKey.AddKey();
				key3.SetPosition(glm::vec3(24 * 32.0, 17 * 32.0, 0.0));
			}
		}

		if (managerKey.CanOpenGate())
		{
			gate.UpdateSprite();
			gate.DrawSprite();

			if (gate.CheckColision(character))
			{
				managerKey.ResetKeys();
				character.SetPosition(glm::vec3(17 * 32.0, 4 * 32.0, 0.0));
				key1.SetPosition(glm::vec3(17 * 32.0, 6 * 32.0, 0.0));
				key2.SetPosition(glm::vec3(7 * 32.0, 14 * 32.0, 0.0));
				key3.SetPosition(glm::vec3(9 * 32.0, 12 * 32.0, 0.0));
			}
		}

		timer.Finish();

		double waitingTime = timer.calcWaitingTime(24, timer.getElapsedTimeMs());

		if (waitingTime)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds((int)waitingTime));
		}

		glfwSwapBuffers(window);
	}
	glfwTerminate();
	return 0;
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (key == GLFW_KEY_A && action == GLFW_PRESS)
	{
		character.SetAnimation(3);
		character.MoveLeft();
	}
	else if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{
		character.SetAnimation(2);
		character.MoveRight();
	}
	else if (key == GLFW_KEY_W && action == GLFW_PRESS)
	{
		character.MoveUp();
		character.SetAnimation(4);

	}
	else if (key == GLFW_KEY_S && action == GLFW_PRESS)
	{
		character.MoveDown();
		character.SetAnimation(0);
	}


	if (action == GLFW_RELEASE)
	{
		character.SetAnimation(1);
	}
}

int setupTexture(string filePath, int& width, int& height)
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
		if (nrChannels == 3)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		else 
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



