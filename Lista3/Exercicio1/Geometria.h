#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"


class Geometria
{
protected:

	GLuint VAO;
	GLuint texID;
	glm::vec3 position, dimension, axis;
	float colorR, colorG, colorB;
	float speed;

	Shader* shader;

public:
	Geometria() {}
	~Geometria() { glDeleteVertexArrays(1, &VAO); }

	inline void SetTexId(GLuint texID) { this->texID = texID; }
	inline void SetPosition(glm::vec3 position) { this->position = position; }
	inline void SetDimension(glm::vec3 dimension) { this->dimension = dimension; }
	inline void SetShader(Shader* shader) { this->shader = shader; }
	inline void SetColor(float r, float g, float b) { colorR = r, colorG = g, colorB = b; }

	inline void MoveLeft() { position.x -= speed; }
	inline void MoveRight() { position.x += speed; }
	inline void MoveUp() { position.y -= speed; }
	inline void MoveDown() { position.y += speed; }


	void InitializeGeometria();
	void UpdateGeometria();
	void DrawGeometria();
};

