#include <iostream>
#include <string>
#include <assert.h>

using namespace std;
#include "Geometria.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

const GLuint WIDTH = 800, HEIGHT = 600;

Geometria square1, square2, square3;

float randomFloat()
{
	return (float)(rand()) / (float)(RAND_MAX);
}

int main()
{

	glfwInit();


	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, " Lista 3 - Exercicio 1, 2 e 3 - Igor Flores", nullptr, nullptr);
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


	Shader shader("../../Shaders/Lista3VS.vs", "../../Shaders/Lista3FS.fs");

	shader.Use();
	glm::mat4 projection = glm::ortho(0.0, 800.0, 600.0, 0.0, -1.0, 1.0);
	shader.setMat4("projection", glm::value_ptr(projection));


	square1.InitializeGeometria();
	square1.SetPosition(glm::vec3(10.0, 590.0, 0));
	square1.SetDimension(glm::vec3(100.0, 100.0, 0));
	square1.SetShader(&shader);

	square2.InitializeGeometria();
	square2.SetPosition(glm::vec3(380.0, 280.0, 0));
	square2.SetDimension(glm::vec3(400.0, 400.0, 0));
	square2.SetColor(0.0f, 0.0f, 0.0f);
	square2.SetShader(&shader);

	square3.InitializeGeometria();
	square3.SetPosition(glm::vec3(420.0, 320.0, 0));
	square3.SetDimension(glm::vec3(400.0, 400.0, 0));
	square3.SetColor(1.0f, 1.0f, 1.0f);
	square3.SetShader(&shader);


	glLineWidth(5);
	glPointSize(8);


	while (!glfwWindowShouldClose(window))
	{

		glfwPollEvents();

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);



		for (int x = 0; x <= 80; x++)
		{
			for (int y = 0; y <= 60; y++)
			{
				square1.SetPosition(glm::vec3(x * 10.0, y * 10.0, 0));
				square1.SetColor(randomFloat(), randomFloat(), randomFloat());
				square1.UpdateGeometria();
				square1.DrawGeometria();

			}

		}

		square2.UpdateGeometria();
		square2.DrawGeometria();

		square3.UpdateGeometria();
		square3.DrawGeometria();

		glBindVertexArray(0);


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
		square2.MoveLeft();
		square3.MoveLeft();
	}
	else if (key == GLFW_KEY_D)
	{
		square2.MoveRight();
		square3.MoveRight();
	}
	else if (key == GLFW_KEY_W)
	{
		square2.MoveUp();
		square3.MoveUp();
	}
	else if (key == GLFW_KEY_S)
	{
		square2.MoveDown();
		square3.MoveDown();
	}
}


