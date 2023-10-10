#include <iostream>
#include <string>
#include <assert.h>

using namespace std;

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"



void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);


int setupGeometry();

const GLuint WIDTH = 800, HEIGHT = 600;


int main()
{

	glfwInit();


	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, " Lista 3 - Exercicio 1 - Igor Flores", nullptr, nullptr);
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

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);



	Shader shader("../../Shaders/Lista3VS.vs", "../../Shaders/Lista3FS.fs");

	GLuint VAO = setupGeometry();


	shader.Use();

	glm::mat4 projection = glm::ortho(0.0, 800.0, 600.0, 0.0, -1.0, 1.0);
	shader.setMat4("projection", glm::value_ptr(projection));


	glLineWidth(5);
	glPointSize(8);


	while (!glfwWindowShouldClose(window))
	{

		glfwPollEvents();

		
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glBindVertexArray(VAO);

		glm::mat4 model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(400.0, 300.0, 0.0));
		model = glm::scale(model, glm::vec3(300.0, 300.0, 1.0));
		shader.setMat4("model", glm::value_ptr(model));

		glDrawArrays(GL_TRIANGLES, 0, 6);



		glBindVertexArray(0);


		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);
	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}


int setupGeometry()
{
	GLfloat vertices[] = {
		//xyz rgb
		-0.3,  0.5, 0.0, 1.0, 0.0, 0.0, //v0
		 0.0,  0.0, 0.0, 0.0, 1.0, 0.0,//v1
		 0.3,  0.5, 0.0, 0.0, 0.0, 1.0 //v2 
	};

	GLuint VBO, VAO;

	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);


	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0);

	return VAO;
}

