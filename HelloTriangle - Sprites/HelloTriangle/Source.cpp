#include <iostream>
#include <string>
#include <assert.h>
#include <stb_image.h>
#include "Sprite.h"
#include "Timer.h"

using namespace std;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

int setupTexture(string filePath, int &width, int &height);

Sprite character;

const GLuint WIDTH = 800, HEIGHT = 600;

int main()
{
	
	glfwInit();


	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Sprites e movimentacoes! - Igor Flores", nullptr, nullptr);
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
	
	Shader shader("../Shaders/HelloTriangle.vs", "../Shaders/HelloTriangle.fs");

	int spriteWidth, spriteHeight;
	GLuint texIdle = setupTexture("../../textures/characters/PNG/Rogue/rogue.png", spriteWidth, spriteHeight);

	character.InitializeSprite(2, 6);
	character.SetTexId(texIdle);
	character.SetPosition(glm::vec3(100.0, 150.0, 0));
	character.SetDimension(glm::vec3(spriteWidth, spriteHeight, 0));
	character.SetShader(&shader);

	GLuint texBd = setupTexture("../../textures/backgrounds/PNG/Postapocalypce4/Pale/postapocalypse4.png", spriteWidth, spriteHeight);

	Sprite background;

	background.InitializeSprite();
	background.SetTexId(texBd);
	background.SetPosition(glm::vec3(400.0, 300.0, 0));
	background.SetDimension(glm::vec3(spriteWidth / 2, spriteHeight / 2, 0));
	background.SetShader(&shader);



	shader.Use();
	
	glm::mat4 projection = glm::ortho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);
	shader.setMat4("projection", glm::value_ptr(projection));

	glActiveTexture(GL_TEXTURE0);
	

	shader.setInt("texBuffer", 0);

	//transparencia das sprites
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//profundidade das sprites
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

	if (key == GLFW_KEY_A)
	{
		character.SetAnimation(1);
		character.MoveLeft();
	}
	else if (key == GLFW_KEY_D)
	{
		character.SetAnimation(1);
		character.MoveRight();
	}
	else if (key == GLFW_KEY_W)
	{
		character.MoveUp();
	}
	else if (key == GLFW_KEY_S)
	{
		character.MoveDown();
	}
	
	
	if(action == GLFW_RELEASE)
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

