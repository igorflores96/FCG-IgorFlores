#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"


class Sprite
{
protected:

	GLuint VAO;
	GLuint texID;
	glm::vec3 position, dimension, axis;
	float angle, speed, ds, dt;
	int nAnimations, nFrames, iAnimation, iFrame;
	bool hasColected;

	Shader* shader;

public:
	Sprite() {}
	~Sprite() { glDeleteVertexArrays(1, &VAO); }

	inline void SetTexId(GLuint texID) { this->texID = texID; }
	inline void SetPosition(glm::vec3 position) { this->position = position; }
	inline void SetDimension(glm::vec3 dimension) { this->dimension.x = dimension.x / nFrames; this->dimension.y = dimension.y / nAnimations; }
	inline void SetShader(Shader* shader) { this->shader = shader; }
	inline void SetAnimation(int iAnimate) { this->iAnimation = iAnimate; }
	inline void SetColected(bool status) { this->hasColected = status; }
	inline glm::vec3 GetPosition() { return position; }
	inline glm::vec3 GetDimension() { return dimension; }



	inline void MoveLeft() { position.x -= speed; }
	inline void MoveRight() { position.x += speed; }
	inline void MoveUp() { position.y += speed; }
	inline void MoveDown() { position.y -= speed; }




	void InitializeSprite(int nAnimations = 1, int nFrames = 1);
	void UpdateSprite();
	void DrawSprite();
	bool HasColected();
	bool CheckColision(Sprite &collisor);
};

