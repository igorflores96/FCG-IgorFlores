/* Hello Triangle - código adaptado de https://learnopengl.com/#!Getting-started/Hello-Triangle
 *
 * Adaptado por Rossana Baptista Queiroz
 * para a disciplina de Processamento Gráfico - Unisinos
 * Versão inicial: 7/4/2017
 * Última atualização em 14/08/2023
 *
 */

#include <iostream>
#include <string>
#include <assert.h>

using namespace std;

// GLAD
#include <glad/glad.h>

// GLFW
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"



void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);


int setupGeometry();

// Dimensões da janela (pode ser alterado em tempo de execução)
const GLuint WIDTH = 800, HEIGHT = 600;

// Função MAIN
int main()
{

	glfwInit();


	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, " Lista 2 - Exercicio 4 e 5 - Igor Flores", nullptr, nullptr);
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



	Shader shader("../../Shaders/Lista2VS.vs", "../../Shaders/Lista2FS.fs");

	GLuint VAO = setupGeometry();


	shader.Use();

	glm::mat4 projection = glm::ortho(0.0, 800.0, 600.0, 0.0, -1.0, 1.0); //glm::mat4 projection = glm::ortho(-10.0, 10.0, -10.0, 10.0, -1.0, 1.0);
	shader.setMat4("projection", glm::value_ptr(projection));


	glLineWidth(5);
	glPointSize(8);

	// Loop da aplicação - "game loop"
	while (!glfwWindowShouldClose(window))
	{

		glfwPollEvents();

		// Limpa o buffer de cor
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glBindVertexArray(VAO);

		int width, height;
		glfwGetFramebufferSize(window, &width, &height);

		

		glm::mat4 model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(400.0, 300.0, 0.0));
		model = glm::scale(model, glm::vec3(300.0, 300.0, 1.0));
		shader.setMat4("model", glm::value_ptr(model));

		glViewport(width / 2, height / 2, width / 2, height / 2); // Direita Cima

		glDrawArrays(GL_TRIANGLES, 0, 6);
		glDrawArrays(GL_LINE_LOOP, 0, 3);
		glDrawArrays(GL_LINE_LOOP, 3, 3);
		glDrawArrays(GL_POINTS, 0, 6);

		glViewport(0, 0, width / 2, height / 2); // Esquerda Baixo

		glDrawArrays(GL_TRIANGLES, 0, 6);
		glDrawArrays(GL_LINE_LOOP, 0, 3);
		glDrawArrays(GL_LINE_LOOP, 3, 3);
		glDrawArrays(GL_POINTS, 0, 6);

		glViewport(0, height / 2, width / 2, height / 2); // Esquerda cima

		glDrawArrays(GL_TRIANGLES, 0, 6);
		glDrawArrays(GL_LINE_LOOP, 0, 3);
		glDrawArrays(GL_LINE_LOOP, 3, 3);
		glDrawArrays(GL_POINTS, 0, 6);

		glViewport(width / 2, 0, width / 2, height / 2); // Direita Baixo

		glDrawArrays(GL_TRIANGLES, 0, 6);
		glDrawArrays(GL_LINE_LOOP, 0, 3);
		glDrawArrays(GL_LINE_LOOP, 3, 3);
		glDrawArrays(GL_POINTS, 0, 6);

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
		//x   y     z
		-0.1,  0.3, 0.0, 1.0, 0.0, 0.0, //v0
		 0.0,  0.0, 0.0, 0.0, 1.0, 0.0,//v1
		 0.1,  0.3, 0.0, 0.0, 0.0, 1.0,//v2 

		 0.0,  0.0, 0.0, 1.0, 0.0, 0.0,//v3
		-0.1, -0.3, 0.0, 0.0, 1.0, 0.0,//v4
		 0.1, -0.3, 0.0, 0.0, 0.0, 1.0,//v5 
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

