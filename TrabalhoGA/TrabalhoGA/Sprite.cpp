#include "Sprite.h"

void Sprite::InitializeSprite(int nAnimations, int nFrames)
{
	speed = 5.0;
	this->nAnimations = nAnimations;
	this->nFrames = nFrames;
	iAnimation = 0;
	iFrame = 0;

	ds = 1.0 / (float)nFrames;
	dt = 1.0 / (float)nAnimations;

	GLfloat vertices[] = {
		//xyz rbg st/uv
		-0.5,  0.5, 0.0, 1.0, 0.0, 0.0, 0.0, dt,  //v0
		-0.5, -0.5, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0,  //v1
		 0.5,  0.5, 0.0, 0.0, 0.0, 1.0, ds, dt,  //v2

		-0.5, -0.5, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0,  //v1
		 0.5, -0.5, 0.0, 0.0, 1.0, 0.0, ds, 0.0,  //v3
		 0.5,  0.5, 0.0, 0.0, 0.0, 1.0, ds, dt  //v2 
	};

	GLuint VBO;

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);

	//geometria
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//cor
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	//textura
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Sprite::UpdateSprite()
{
	shader->Use();
	glm::mat4 model = glm::mat4(1);
	model = glm::translate(model, position);
	model = glm::scale(model, dimension);
	shader->setMat4("model", glm::value_ptr(model));

	shader->setVec2("offset", iFrame * ds, iAnimation * dt);

	iFrame = (iFrame + 1) % nFrames;
}

void Sprite::DrawSprite()
{
	shader->Use();
	glBindVertexArray(VAO);
	glBindTexture(GL_TEXTURE_2D, texID);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}
