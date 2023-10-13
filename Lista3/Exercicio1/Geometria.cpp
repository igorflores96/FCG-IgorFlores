#include "Geometria.h"

void Geometria::InitializeGeometria()
{
	GLfloat vertices[] = {
		//xyz
		-0.1,  0.1, 0.0,
		-0.1, -0.1, 0.0,
		 0.1,  0.1, 0.0,

		-0.1, -0.1, 0.0,
		 0.1, -0.1, 0.0,
		 0.1,  0.1, 0.0,
	};

	speed = 5.0f;

	GLuint VBO;

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);

	//geometria
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Geometria::UpdateGeometria()
{

	shader->Use();
	glm::mat4 model = glm::mat4(1);
	model = glm::translate(model, position);
	model = glm::scale(model, dimension);
	shader->setMat4("model", glm::value_ptr(model));
}

void Geometria::DrawGeometria()
{
	shader->Use();
	glBindVertexArray(VAO);
	GLint colorLoc = glGetUniformLocation(shader->ID, "inputColor");
	glUniform4f(colorLoc, colorR, colorG, colorB, 1.0f);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindVertexArray(0);
}
