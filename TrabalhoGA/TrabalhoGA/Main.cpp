#include <iostream>
#include <string>
#include <assert.h>
#include <stb_image.h>
#include "Sprite.h"
#include "Timer.h"

using namespace std;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

int setupTexture(string filePath, int& width, int& height);

Sprite character, background, mazeWall;

const GLuint WIDTH = 800, HEIGHT = 600;

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
	GLuint texIdle = setupTexture("../../textures/characters/PNG/Rogue/Run_Attack/green.png", spriteWidth, spriteHeight);

	character.InitializeSprite(1, 1);
	character.SetTexId(texIdle);
	character.SetPosition(glm::vec3(32.0, 32.0, 0.0));
	character.SetDimension(glm::vec3(spriteWidth, spriteHeight, 0));
	character.SetShader(&shader);

	GLuint texBd = setupTexture("../../textures/backgrounds/PNG/Postapocalypce4/Pale/postapocalypse4.png", spriteWidth, spriteHeight);

	background.InitializeSprite(1, 1);
	background.SetTexId(texBd);
	background.SetPosition(glm::vec3(400.0, 300.0, 0));
	background.SetDimension(glm::vec3(spriteWidth / 2, spriteHeight / 2, 0));
	background.SetShader(&shader);

	GLuint texWall = setupTexture("../../textures/characters/PNG/Rogue/Run_Attack/red.png", spriteWidth, spriteHeight);

	mazeWall.InitializeSprite(1, 1);
	mazeWall.SetTexId(texWall);
	mazeWall.SetDimension(glm::vec3(spriteWidth, spriteHeight, 0));
	mazeWall.SetShader(&shader);

	shader.Use();

	glm::mat4 projection = glm::ortho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);
	shader.setMat4("projection", glm::value_ptr(projection));
	glActiveTexture(GL_TEXTURE0);
	shader.setInt("texBuffer", 0);

	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_ALWAYS);

	Timer timer;

	while (!glfwWindowShouldClose(window))
	{
		timer.Start();

		glfwPollEvents();


		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//fundo
		background.UpdateSprite();
		background.DrawSprite();

		//personagem
		character.UpdateSprite();
		character.DrawSprite();
		
		for (int x = 0; x < WIDTH / 80; x++)
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
		character.SetAnimation(1);
		character.MoveLeft();
	}
	else if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{
		character.SetAnimation(1);
		character.MoveRight();
	}
	else if (key == GLFW_KEY_W && action == GLFW_PRESS)
	{
		character.MoveUp();
	}
	else if (key == GLFW_KEY_S && action == GLFW_PRESS)
	{
		character.MoveDown();
	}


	if (action == GLFW_RELEASE)
	{
		character.SetAnimation(0);
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

